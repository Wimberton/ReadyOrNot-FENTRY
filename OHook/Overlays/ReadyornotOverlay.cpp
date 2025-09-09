#include "ReadyornotOverlay.h"
#include "DetourManager.h"

#include "console.hpp"
#include "ImGuiExt.h"
#include "SDKExt.h"
#include "Utils.h"
#include "Configuration.h"
#include "LocalizationManager.h"
#include "ActorCache.h"
#include "Overlays/ESP.h"

#include "Modules/ESP_VisualSettings.h"
#include "Modules/Player_ModSettings.h"
#include "Modules/Weapon_ModSettings.h"
#include "Modules/World_ModSettings.h"

#include "Modules/Fentry_Settings.h"
#include "Features/WorldFeatures.h"

#include <Windows.h>
#include <algorithm>
#include <thread>
#include <fstream>
#include <TlHelp32.h>
#include <imgui_internal.h>
#include <Fonts.h>
#include <unordered_set>

using namespace SDK;

std::vector<std::string> debugger;
DetourManager gDetourManager;

bool waitingForKey = false;
bool waitingForTeleportKey = false;
bool waitingForUnifiedTeleportKey = false;
bool waitingForSpeedKey = false;
bool waitingForNoClipKey = false;
bool waitingForIncapacitateKey = false;
bool waitingForInstantWinKey = false;
bool waitingForInstantLoseKey = false;
bool waitingForArrestAllKey = false;
bool waitingForReportAllKey = false;
bool waitingForCollectAllEvidenceKey = false;

const char* boneTargets[] = { "Head", "Neck", "Spine", "Chest", "Pelvis" };
const char* espBoxStyles[] = { "2D Box", "Cornered Box" };
const char* ReadyornotOverlay::themes[4] = { "Main", "Spectrum Light", "Magma", "Custom Theme" };

float tempPlayerColor[4];

int selectedBoxStyle = Configuration::cfg_AimbotBox;

// ======== DRAWING STUFF ======== //

void ReadyornotOverlay::DrawGuiESP() {    
    ReadyornotESP::DrawGuiESP();
}

void ReadyornotOverlay::DrawGuiFOVCircle() {
    ReadyornotESP::DrawGuiFOVCircle();
}

void ReadyornotOverlay::DrawHUD() {
    static bool bConfigLoaded = false;
    if (!bConfigLoaded) {
        Configuration::Load(static_cast<ReadyornotOverlay*>(OverlayBase::Instance));
        LocalizationManager::Initialize();
        bConfigLoaded = true;
    }

    ReadyornotOverlay* Overlay = static_cast<ReadyornotOverlay*>(OverlayBase::Instance);
    WorldFeatures::Func_UpdateCurrentLevel(Overlay);

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::SetNextWindowBgAlpha(0.50f);
    ImGuiStyle& style = ImGui::GetStyle();
    float prevRounding = style.WindowRounding;
    style.WindowRounding = 5.0f;

    // Watermark
    if (Configuration::bShowWatermark) {
        ReadyornotOverlay* Overlay = static_cast<ReadyornotOverlay*>(OverlayBase::Instance);
        std::string currentMap = Overlay ? Overlay->CurrentMap : "Loading world...";
        
        std::string watermarkText = "RONFentry - Ready or Not Cheat - " + currentMap;
        float textW = ImGui::CalcTextSize(watermarkText.c_str()).x;
        ImGui::SetNextWindowPos({ (io.DisplaySize.x - textW) * 0.5f, 10.0f });
        ImGui::Begin("Watermark", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoFocusOnAppearing |
            ImGuiWindowFlags_NoNav);
        ImGui::Text("%s", watermarkText.c_str());
        ImGui::End();
    }
    
    style.WindowRounding = prevRounding;

    /*
    * Theme loading
    */
    if (getTheme) {
        switch (Configuration::selectedTheme) {
        case 0:
            ImGui::StyleColorsDark();
            break;
        case 1:
            ImGui::Spectrum::StyleColorsSpectrum();
            break;
        case 2:
            ImGui::Magma::StyleColorsMagma();
            break;
        case 3:
            Configuration::ApplyCustomTheme();
            break;
        default:
            ImGui::StyleColorsDark();
            break;
        }
        getTheme = false;
    }

    /*
     * Notification rendering
     */
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
    ImVec4 windowBg = ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_WindowBg));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(windowBg.x, windowBg.y, windowBg.z, 1.00f));
    ImGui::RenderNotifications();
    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(1);

    /*
     * Notification(s) for first use-case scenario
     */
    static bool displayedFirstUseNotif, displayedCorruptConfigNotif = false;
    if (Configuration::bFirstUse && !displayedFirstUseNotif) {
        ImGui::InsertNotification({ ImGuiToastType::Info, 8000, LOC("notification.first_use").c_str() });
        displayedFirstUseNotif = true;
    }

    APlayerController* PC = GetAPC();
    AReadyOrNotPlayerController* ARONPC = GetARONPC();

    static APlayerController* s_HookedPC = nullptr;
    static AReadyOrNotPlayerState* s_HookedPS = nullptr;
    static AReadyOrNotCharacter* s_HookedARONChar = nullptr;
    static UCharacterHealthComponent* s_HookedHealthComp = nullptr;
    static UCharacterMovementComponent* s_HookedARONMovement = nullptr;
    static ABaseWeapon* s_HookedWeapon = nullptr;
    static AReadyOrNotCharacter* s_HookedRONChar = nullptr;
    static ACharacter* s_HookedCharacter = nullptr;
    static AHUD* s_HookedHUD = nullptr;

    // Hook PC
    if (PC && PC != s_HookedPC) {
        gDetourManager.SetupDetour(PC);
        s_HookedPC = PC;
    }

    // Hook PlayerState
    if (PC && PC->PlayerState && PC->PlayerState != s_HookedPS) {
        gDetourManager.SetupDetour(PC->PlayerState);
        s_HookedPS = static_cast<AReadyOrNotPlayerState*>(PC->PlayerState);
    }

    // Hook Ready or Not character + components
    AReadyOrNotCharacter* ARONChar = GetARONCharacter();
    if (ARONChar && ARONChar != s_HookedARONChar) {
        gDetourManager.SetupDetour(ARONChar);
        s_HookedARONChar = ARONChar;
    }

    // Hook generic Ready or Not character
    AReadyOrNotCharacter* RONChar = GetAHCharacter();
    if (RONChar && RONChar != s_HookedRONChar) {
       gDetourManager.SetupDetour(RONChar);
       s_HookedRONChar = RONChar;
    }

    // Hook generic pawn
    ACharacter* Char = static_cast<ACharacter*>(PC ? PC->K2_GetPawn() : nullptr);
    if (Char && Char != s_HookedCharacter) {
       gDetourManager.SetupDetour(Char);
       s_HookedCharacter = Char;
    }

    // Hook HUD once
    if (PC && PC->MyHUD && PC->MyHUD != s_HookedHUD) {
        gDetourManager.SetupDetour(PC->MyHUD);
        s_HookedHUD = PC->MyHUD;
    }
}

void ReadyornotOverlay::DrawOverlay() {
    bool show = true;
    const ImGuiIO& io = ImGui::GetIO();
    constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;

    const auto center_pos = ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
    const auto window_size = ImVec2(Configuration::windowSizeX, Configuration::windowSizeY);
    const auto window_pos = ImVec2(center_pos.x - window_size.x * 0.5f, center_pos.y - window_size.y * 0.5f);

    ImGui::SetNextWindowPos(window_pos, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(window_size, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowBgAlpha(0.98f);

    const auto WindowTitle = LOC("window.main_title");
    ReadyornotOverlay* Overlay = static_cast<ReadyornotOverlay*>(OverlayBase::Instance);

    if (ImGui::Begin(WindowTitle.data(), &show, window_flags)) {
        
        /*
         * First use case-scenario bool
         */
        if (Configuration::bFirstUse) {
            Configuration::bFirstUse = false;
            Configuration::Save();
        }

        static int OpenTab = 0;
        static int previousLanguage = -1;
        static bool needsTabRestore = false;

        int currentLanguage = static_cast<int>(LocalizationManager::GetCurrentLanguage());
        if (previousLanguage != -1 && previousLanguage != currentLanguage) {
            needsTabRestore = true;
        }
        previousLanguage = currentLanguage;

        if (ImGui::IsMouseDragging(0)) {
            Configuration::windowSizeX = static_cast<float>(ImGui::GetWindowSize().x);
            Configuration::windowSizeY = static_cast<float>(ImGui::GetWindowSize().y);
            Configuration::Save();
        }

        ImGuiTabItemFlags tabFlags0 = (OpenTab == 0 && needsTabRestore) ? ImGuiTabItemFlags_SetSelected : 0;
        ImGuiTabItemFlags tabFlags1 = (OpenTab == 1 && needsTabRestore) ? ImGuiTabItemFlags_SetSelected : 0;
        ImGuiTabItemFlags tabFlags2 = (OpenTab == 2 && needsTabRestore) ? ImGuiTabItemFlags_SetSelected : 0;
        ImGuiTabItemFlags tabFlags3 = (OpenTab == 3 && needsTabRestore) ? ImGuiTabItemFlags_SetSelected : 0;
        ImGuiTabItemFlags tabFlags4 = (OpenTab == 4 && needsTabRestore) ? ImGuiTabItemFlags_SetSelected : 0;

        if (ImGui::BeginTabBar("OverlayTabs")) {
            if (ImGui::BeginTabItem((ICON_FA_EYE " " + LOC("tab.visuals") + "##VisualsTab").c_str(), nullptr, tabFlags0)) {
                OpenTab = 0;
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem((ICON_FA_PERSON " " + LOC("tab.player_mods") + "##PlayerModsTab").c_str(), nullptr, tabFlags1)) {
                OpenTab = 1;
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem((ICON_FA_CROSSHAIRS " " + LOC("tab.weapon_mods") + "##WeaponModsTab").c_str(), nullptr, tabFlags2)) {
                OpenTab = 2;
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem((ICON_FA_GLOBE " " + LOC("tab.world_mods") + "##WorldModsTab").c_str(), nullptr, tabFlags3)) {
                OpenTab = 3;
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem((ICON_FA_GEAR " " + LOC("tab.settings_hotkeys") + "##SettingsHotkeysTab").c_str(), nullptr, tabFlags4)) {
                OpenTab = 4;
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }

        if (needsTabRestore) {
            needsTabRestore = false;
        }

        AReadyOrNotPlayerController* ReadyOrNotPlayerController = GetARONPC();
        AReadyOrNotCharacter* ReadyOrNotCharacter = GetARONCharacter();

        constexpr float f1000 = 1000.0f, f5 = 5.f, f1 = 1.f;

        if (OpenTab == 0) {
            ESP_VisualSettings::Show();
        }
        else if (OpenTab == 1) {
            Player_ModSettings::Show();
        }
        else if (OpenTab == 2) {
            Weapon_ModSettings::Show();
        }
        else if (OpenTab == 3) {
            World_ModSettings::Show();
        }
        else if (OpenTab == 4) {
            Fentry_Settings::Show();
        }
    }

    ImGui::End();

    if (!show)
        ShowOverlay(false);
}