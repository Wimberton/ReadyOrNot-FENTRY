#include "WorldFeatures.h"
#include "Configuration.h"
#include "Utils.h"
#include "SDKExt.h"
#include "LocalizationManager.h"
#include "ImGuiExt.h"
#include "ActorCache.h"
#include <chrono>
#include <Windows.h>

using namespace SDK;

namespace WorldFeatures {

    void Func_UpdateCurrentLevel(ReadyornotOverlay* Overlay) {
        if (!Overlay)
            return;

        UWorld* GWorld = GetWorld();
        if (!GWorld)
            return;
    
        if (Overlay->CurrentLevel != GWorld->PersistentLevel) {
            Overlay->CurrentLevel = GWorld->PersistentLevel;
            
            FString LevelName = UGameplayStatics::GetCurrentLevelName(GWorld, false);
            std::string levelNameStr = LevelName.ToString();
            
            if (levelNameStr != Overlay->CurrentLevelName) {
                Overlay->CurrentLevelName = levelNameStr;

                if (levelNameStr.find("MainMenu_V2") != std::string::npos) {
                    Overlay->CurrentMap = "Startup/Login";
                } else if (levelNameStr.find("TransitionMap") != std::string::npos) {
                    Overlay->CurrentMap = "Loading...";
                } else if (levelNameStr.find("RoN_Station_DLC02_Core") != std::string::npos) {
                    Overlay->CurrentMap = "Los Suenos Police HQ";
                } else {
                    Overlay->CurrentMap = levelNameStr;
                }
            }
        }
    }

    void Func_UnlitMode() {
        UWorld* GWorld = GetWorld();
        if (!GWorld)
            return;

        if (!GWorld->OwningGameInstance)
            return;

        APlayerController* PlayerController = GetAPC();
        if (!PlayerController || !IsActorValid(PlayerController))
            return;
            
        if (!PlayerController->PlayerCameraManager || !IsActorValid(PlayerController->PlayerCameraManager))
            return;

        UGameInstance* GameInstance = GWorld->OwningGameInstance;
        if (!GameInstance || !GameInstance->LocalPlayers || GameInstance->LocalPlayers.Num() <= 0) {
            return;
        }

        const ULocalPlayer* LocalPlayer = GameInstance->LocalPlayers[0];
        if (!LocalPlayer || !LocalPlayer->PlayerController || !LocalPlayer->PlayerController->IsA(APlayerController::StaticClass())) {
            return;
        }

        UGameViewportClient* GameViewportClient = LocalPlayer->ViewportClient;
        if (!GameViewportClient) {
            return;
        }

        uint8_t* ViewportClientPtr = reinterpret_cast<uint8_t*>(GameViewportClient);
        uint8_t* ViewModePtr = ViewportClientPtr + 0xB0;
        
        uint8_t currentViewMode = *ViewModePtr;
        uint8_t desiredViewMode = Configuration::cfg_EnableUnlitMode ? 0x1 : 0x3;
        
        if (currentViewMode != desiredViewMode) {
            *ViewModePtr = desiredViewMode;
        }
    }
}
