#include "Configuration.h"
#include "ReadyornotOverlay.h"
#include "Utils.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <type_traits>

namespace fs = std::filesystem;

#pragma region VarsInit

std::string Configuration::JsonConfigFile = "";
bool Configuration::ConfigLoaded = false;

// Config Version
int Configuration::Version = 1;

// Window settings
float Configuration::windowSizeX = 1150.0f;
float Configuration::windowSizeY = 500.0f;

// Visual settings
bool Configuration::bFirstUse = true;
bool Configuration::bShowWatermark = true;
bool Configuration::bShowSpectators = false;
float Configuration::cfg_FOVRadius = 100.0f;
float Configuration::cfg_CircleAlpha = 0.5f;
float Configuration::cfg_LootAlpha = 1.0f;
float Configuration::cfg_ESPThickness = 1.0f;
float Configuration::cfg_MaxPlayerESPDistance = 100000.0f;

int Configuration::selectedTheme = 0;
int Configuration::cfg_SelectedLanguage = 0;
std::map<int, ImVec4> Configuration::customColors = {};

// Aimbot settings
bool Configuration::cfg_EnableAimbot = false;
bool Configuration::cfg_AllowOtherTargeting = false;
bool Configuration::cfg_SilentAimbotEnabled = false;
bool Configuration::cfg_AimVisCheck = true;
bool Configuration::cfg_AimbotNoSpread = false;
bool Configuration::cfg_AimbotNoRecoil = false;
bool Configuration::cfg_AimbotNoSway = false;
float Configuration::cfg_AimbotFOV = 140.0f;
float Configuration::cfg_AimbotSmoothing = 80.0f;
int Configuration::cfg_AimbotTargetBone = 0;
int Configuration::cfg_AimbotBox = 0;
int Configuration::cfg_AimbotKey = VK_RBUTTON;
int Configuration::cfg_AimTarget = 0;

// Weapon settings
bool Configuration::cfg_InfiniteAmmo = false;
bool Configuration::cfg_InstantReload = false;
int Configuration::cfg_CustomAmmoCount = 100;

// Movement settings
bool Configuration::cfg_EnableNoClip = false;
bool Configuration::cfg_PreviousNoclipState = false;
bool Configuration::cfg_EnableSpeedhack = false;
bool Configuration::cfg_DoUnlimitedStamina = false;
float Configuration::cfg_speedPlayerValue = 1.0f;
int Configuration::cfg_SpeedKey = VK_XBUTTON2;
int Configuration::cfg_NoClipKey = VK_RSHIFT;

// Player settings
bool Configuration::cfg_DoNoFlash = false;
bool Configuration::cfg_DoNoWeight = false;
bool Configuration::cfg_NoStagger = false;
bool Configuration::cfg_UnlockAllItems = false;
bool Configuration::cfg_EnableGodmode = false;
bool Configuration::cfg_NoSuspectFirefight = false;
bool Configuration::cfg_DisarmAllSuspects = false;
bool Configuration::cfg_ForceSuspectSurrender = false;
bool Configuration::cfg_AutoComplySuspects = false;

// Trap settings
bool Configuration::cfg_DisableAllTraps = false;

// Teleport settings
bool Configuration::cfg_TeleportToTarget = false;
int Configuration::cfg_TeleportKey = VK_XBUTTON1;
int Configuration::cfg_TeleportMethod = 0;

// Unified Teleport settings
bool Configuration::cfg_EnableTPTarget = false;
int Configuration::cfg_TPTargetKey = VK_F6;
bool Configuration::cfg_SmallerTPTargeting = false;
float Configuration::cfg_TPFOVRadius = 50.0f;
float Configuration::cfg_ActorTeleportOffset = 100.0f;
float Configuration::cfg_TPNoTargetDistance = 15.0f;

// Gamemode settings
int Configuration::cfg_IncapacitateAllKey = VK_F1;
int Configuration::cfg_InstantWinKey = VK_F2;
int Configuration::cfg_InstantLoseKey = VK_F3;
int Configuration::cfg_ArrestAllKey = VK_F4;
int Configuration::cfg_ReportAllKey = VK_F5;
int Configuration::cfg_CollectAllEvidenceKey = VK_F7;

// General ESP settings (affect all character types)
bool Configuration::cfg_DrawFOVCircle = false;
bool Configuration::cfg_DrawESPBoxes = false;
bool Configuration::cfg_DrawESPNames = false;
bool Configuration::cfg_DrawESPHealth = false;
bool Configuration::cfg_DrawESPBones = false;
bool Configuration::cfg_DrawESPLines = false;
bool Configuration::cfg_DrawESPLinesTop = false;

// Player-specific ESP settings
bool Configuration::cfg_DrawPlayerESP = false;
bool Configuration::cfg_DrawPlayerBoxes = false;
bool Configuration::cfg_DrawPlayerNames = false;
bool Configuration::cfg_DrawPlayerHealth = false;
bool Configuration::cfg_DrawPlayerBones = false;
bool Configuration::cfg_DrawPlayerLines = false;
bool Configuration::cfg_DrawPlayerLinesTop = false;

// AI Character ESP settings
bool Configuration::cfg_DrawSERTRedESP = false;
bool Configuration::cfg_DrawSERTRedBoxes = false;
bool Configuration::cfg_DrawSERTRedNames = false;
bool Configuration::cfg_DrawSERTRedHealth = false;
bool Configuration::cfg_DrawSERTRedBones = false;
bool Configuration::cfg_DrawSERTRedLines = false;

bool Configuration::cfg_DrawSERTBlueESP = false;
bool Configuration::cfg_DrawSERTBlueBoxes = false;
bool Configuration::cfg_DrawSERTBlueNames = false;
bool Configuration::cfg_DrawSERTBlueHealth = false;
bool Configuration::cfg_DrawSERTBlueBones = false;
bool Configuration::cfg_DrawSERTBlueLines = false;

bool Configuration::cfg_DrawSuspectESP = false;
bool Configuration::cfg_DrawSuspectBoxes = false;
bool Configuration::cfg_DrawSuspectNames = false;
bool Configuration::cfg_DrawSuspectHealth = false;
bool Configuration::cfg_DrawSuspectBones = false;
bool Configuration::cfg_DrawSuspectLines = false;

bool Configuration::cfg_DrawCivilianESP = false;
bool Configuration::cfg_DrawCivilianBoxes = false;
bool Configuration::cfg_DrawCivilianNames = false;
bool Configuration::cfg_DrawCivilianHealth = false;
bool Configuration::cfg_DrawCivilianBones = false;
bool Configuration::cfg_DrawCivilianLines = false;

bool Configuration::cfg_DrawSquadESP = false;
bool Configuration::cfg_DrawSquadBoxes = false;
bool Configuration::cfg_DrawSquadNames = false;
bool Configuration::cfg_DrawSquadHealth = false;
bool Configuration::cfg_DrawSquadBones = false;
bool Configuration::cfg_DrawSquadLines = false;

bool Configuration::cfg_DrawWoundedESP = false;
bool Configuration::cfg_DrawWoundedBoxes = false;
bool Configuration::cfg_DrawWoundedNames = false;
bool Configuration::cfg_DrawWoundedHealth = false;
bool Configuration::cfg_DrawWoundedBones = false;
bool Configuration::cfg_DrawWoundedLines = false;

float Configuration::cfg_MaxAIESPDistance = 100000.0f;

// Object ESP settings
bool Configuration::cfg_DrawEvidenceESP = false;
bool Configuration::cfg_DrawCollectedEvidenceESP = false;
bool Configuration::cfg_DrawItemsESP = false;
bool Configuration::cfg_DrawDoorsESP = false;
bool Configuration::cfg_DrawTrapsESP = false;
bool Configuration::cfg_DrawSecurablesESP = false;
float Configuration::cfg_MaxObjectESPDistance = 50000.0f;

// Debug settings
bool Configuration::cfg_ShowDebugClassNames = false;
bool Configuration::cfg_ShowDebugDistance = true;
float Configuration::cfg_DebugMaxDistance = 50000.0f;

// Name Changer
char Configuration::cfg_PlayerNameInput[64] = "";

// FOV settings
bool Configuration::cfg_EnableCustomFOV = false;
float Configuration::cfg_CustomFOV = 90.0f;

// Unlit mode settings
bool Configuration::cfg_EnableUnlitMode = false;

#pragma endregion

static const std::string configDirectory = "C:\\ProgramData\\OriginReadyornot\\config";
static const std::string configFileName = "overlay_config.json";
static const std::string configFilePath = configDirectory + "\\" + configFileName;

static void EnsureDirectoryExists(const std::string& path) {
    fs::path dir(path);
    if (!fs::exists(dir)) {
        fs::create_directories(dir);
    }
}

void Configuration::ParseBool(std::string Key, bool& Var) {
    if (JsonConfigFile.empty()) return;

    if (JsonConfigFile.find(Key) == std::string::npos) return;

    Var = (JsonConfigFile.find("\"" + Key + "\": true") != std::string::npos);
}

void Configuration::ParseBool(std::string Key, bool& Var, bool DefaultValue) {
    Var = DefaultValue;

    ParseBool(Key, Var);
}

void Configuration::ParseString(std::string Key, char* Var, size_t MaxLength) {
    if (JsonConfigFile.empty()) return;

    auto pos = JsonConfigFile.find("\"" + Key + "\":");
    if (pos == std::string::npos) return;

    std::size_t colonPos = JsonConfigFile.find(":", pos);
    if (colonPos == std::string::npos) return;

    std::size_t openQuotePos = JsonConfigFile.find("\"", colonPos + 1);
    if (openQuotePos == std::string::npos) return;

    std::size_t closeQuotePos = JsonConfigFile.find("\"", openQuotePos + 1);
    if (closeQuotePos == std::string::npos) return;

    std::string stringValue = JsonConfigFile.substr(openQuotePos + 1, closeQuotePos - openQuotePos - 1);

    strncpy_s(Var, MaxLength, stringValue.c_str(), MaxLength - 1);
    Var[MaxLength - 1] = '\0';
}

template<typename T>
void Configuration::ParseNumber(std::string Key, T& Var) {
    static_assert(std::is_arithmetic<T>::value, "Template parameter must be a numeric type");

    if (JsonConfigFile.empty()) return;

    auto pos = JsonConfigFile.find("\"" + Key + "\":");
    if (pos == std::string::npos) return;

    std::size_t colonPos = JsonConfigFile.find(":", pos);
    if (colonPos == std::string::npos) return;

    std::size_t start = JsonConfigFile.find_first_not_of(" \t\n\r", colonPos + 1);
    if (start == std::string::npos) return;

    std::size_t end = JsonConfigFile.find_first_of(",\n\r}", start);
    if (end == std::string::npos) end = JsonConfigFile.length();

    std::string numberStr = JsonConfigFile.substr(start, end - start);

    size_t lastChar = numberStr.find_last_not_of(" \t\n\r");
    if (lastChar != std::string::npos) {
        numberStr = numberStr.substr(0, lastChar + 1);
    }

    if constexpr (std::is_integral<T>::value) {
        T oldValue = Var;
        Var = static_cast<T>(std::stoi(numberStr));
    }
    else {
        Var = static_cast<T>(std::stof(numberStr));
    }
}

bool Configuration::ReadJsonFile() {
    if (!fs::exists(configFilePath)) {
        return false;
    }

    std::ifstream configFile(configFilePath);
    std::string line;
    if (configFile.is_open()) {
        while (getline(configFile, line)) {
            JsonConfigFile += line;
        }
        configFile.close();
        return true;
    }

    return false;
}

void Configuration::Load(ReadyornotOverlay* Overlay) {
    if (ConfigLoaded) return;

    if (!ReadJsonFile()) return;

    // Window settings
    ParseNumber("Menu Size X", windowSizeX);
    ParseNumber("Menu Size Y", windowSizeY);

    // Visual settings
    ParseBool("First Use", bFirstUse);
    ParseNumber("Selected Theme", selectedTheme);
    ParseNumber("Selected Language", cfg_SelectedLanguage);
    ParseBool("Watermark", bShowWatermark);
    ParseBool("Show Spectators", bShowSpectators);
    ParseNumber("FOV Circle Radius", cfg_FOVRadius);
    ParseNumber("Circle Alpha", cfg_CircleAlpha);
    ParseNumber("Loot Alpha", cfg_LootAlpha);
    ParseNumber("ESP Thickness", cfg_ESPThickness);
    ParseNumber("Max Player ESP Distance", cfg_MaxPlayerESPDistance);

    // Custom theme colors parsing
    if (JsonConfigFile.find("\"Custom Theme Colors\"") != std::string::npos) {
        // Parse custom colors from JSON
        auto pos = JsonConfigFile.find("\"Custom Theme Colors\"");
        auto startBrace = JsonConfigFile.find("{", pos);
        auto endBrace = JsonConfigFile.find("}", startBrace);

        if (startBrace != std::string::npos && endBrace != std::string::npos) {
            std::string colorsSection = JsonConfigFile.substr(startBrace + 1, endBrace - startBrace - 1);

            // Simple parsing for color entries like "0": {"r": 0.1, "g": 0.2, "b": 0.3, "a": 1.0}
            size_t colorPos = 0;
            while ((colorPos = colorsSection.find("\"", colorPos)) != std::string::npos) {
                auto keyStart = colorPos + 1;
                auto keyEnd = colorsSection.find("\"", keyStart);
                if (keyEnd == std::string::npos) break;

                try {
                    int colorIndex = std::stoi(colorsSection.substr(keyStart, keyEnd - keyStart));

                    // Find the color object
                    auto objStart = colorsSection.find("{", keyEnd);
                    auto objEnd = colorsSection.find("}", objStart);
                    if (objStart != std::string::npos && objEnd != std::string::npos) {
                        std::string colorObj = colorsSection.substr(objStart, objEnd - objStart + 1);

                        float r = 0.0f, g = 0.0f, b = 0.0f, a = 1.0f;

                        // Extract RGBA values
                        auto rPos = colorObj.find("\"r\":");
                        if (rPos != std::string::npos) {
                            auto rStart = colorObj.find_first_not_of(" \t", rPos + 4);
                            auto rEnd = colorObj.find_first_of(",}", rStart);
                            if (rStart != std::string::npos && rEnd != std::string::npos) {
                                r = std::stof(colorObj.substr(rStart, rEnd - rStart));
                            }
                        }

                        auto gPos = colorObj.find("\"g\":");
                        if (gPos != std::string::npos) {
                            auto gStart = colorObj.find_first_not_of(" \t", gPos + 4);
                            auto gEnd = colorObj.find_first_of(",}", gStart);
                            if (gStart != std::string::npos && gEnd != std::string::npos) {
                                g = std::stof(colorObj.substr(gStart, gEnd - gStart));
                            }
                        }

                        auto bPos = colorObj.find("\"b\":");
                        if (bPos != std::string::npos) {
                            auto bStart = colorObj.find_first_not_of(" \t", bPos + 4);
                            auto bEnd = colorObj.find_first_of(",}", bStart);
                            if (bStart != std::string::npos && bEnd != std::string::npos) {
                                b = std::stof(colorObj.substr(bStart, bEnd - bStart));
                            }
                        }

                        auto aPos = colorObj.find("\"a\":");
                        if (aPos != std::string::npos) {
                            auto aStart = colorObj.find_first_not_of(" \t", aPos + 4);
                            auto aEnd = colorObj.find_first_of(",}", aStart);
                            if (aStart != std::string::npos && aEnd != std::string::npos) {
                                a = std::stof(colorObj.substr(aStart, aEnd - aStart));
                            }
                        }

                        customColors[colorIndex] = ImVec4(r, g, b, a);
                    }
                }
                catch (const std::exception&) {
                    // Skip invalid entries
                }

                colorPos = keyEnd + 1;
            }
        }
    }

    // Aimbot settings
    ParseNumber("Aimbot FOV", cfg_AimbotFOV);
    ParseNumber("Aimbot Smoothing", cfg_AimbotSmoothing);
    ParseNumber("Aim Target", cfg_AimTarget);
    ParseNumber("Aimbot Target Bone", cfg_AimbotTargetBone);
    ParseNumber("Aimbot Box", cfg_AimbotBox);
    ParseNumber("Aimbot Key", cfg_AimbotKey);
    ParseBool("Enable Aimbot", cfg_EnableAimbot);
    ParseBool("Enable Lootable Targeting", cfg_AllowOtherTargeting);
    ParseBool("Enable Silent Aimbot", cfg_SilentAimbotEnabled);
    ParseBool("Enable Visibility Check", cfg_AimVisCheck);
    ParseBool("Enable No-Spread", cfg_AimbotNoSpread);
    ParseBool("Enable No-Recoil", cfg_AimbotNoRecoil);
    ParseBool("Enable No-Sway", cfg_AimbotNoSway);

    // Weapon settings
    ParseBool("Enable Infinite Ammo", cfg_InfiniteAmmo);
    ParseBool("Enable Instant Reload", cfg_InstantReload);
    ParseNumber("Ammo Amount", cfg_CustomAmmoCount);

    // Movement settings
    ParseBool("Enable NoClip", cfg_EnableNoClip);
    ParseBool("NoClip Previous", cfg_PreviousNoclipState);
    ParseBool("Enable Speedhack", cfg_EnableSpeedhack);
    ParseBool("Enable Infinite Stamina", cfg_DoUnlimitedStamina);
    ParseNumber("Speedhack Amount", cfg_speedPlayerValue);
    ParseNumber("Speedhack Key", cfg_SpeedKey);
    ParseNumber("NoClip Key", cfg_NoClipKey);

    // Player settings
    ParseBool("Enable No Flash", cfg_DoNoFlash);
    ParseBool("Enable No Weight", cfg_DoNoWeight);
    ParseBool("Enable No Stagger", cfg_NoStagger);
    ParseBool("Enable Unlock All Items", cfg_UnlockAllItems);
    ParseBool("Enable Godmode", cfg_EnableGodmode);
    ParseBool("No Suspect Firefight", cfg_NoSuspectFirefight);
    ParseBool("Disarm All Suspects", cfg_DisarmAllSuspects);
    ParseBool("Force Suspect Surrender", cfg_ForceSuspectSurrender);
    ParseBool("Auto-Comply Suspects", cfg_AutoComplySuspects);
    
    // Trap settings
    ParseBool("Disable All Traps", cfg_DisableAllTraps);

    // Name Changer
    ParseString("Player Name Input", cfg_PlayerNameInput, sizeof(cfg_PlayerNameInput));

    // FOV settings
    ParseBool("Enable Custom FOV", cfg_EnableCustomFOV);
    ParseNumber("Custom FOV Value", cfg_CustomFOV);

    // Unlit mode settings
    ParseBool("Enable Unlit Mode", cfg_EnableUnlitMode);

    // Teleport settings
    ParseBool("Enable Teleport To Target", cfg_TeleportToTarget);
    ParseNumber("Teleport Key", cfg_TeleportKey);
    ParseNumber("Teleport Method", cfg_TeleportMethod);
    
    // Unified Teleport settings
    ParseBool("Enable Unified Teleport", cfg_EnableTPTarget);
    ParseNumber("Unified Teleport Key", cfg_TPTargetKey);
    ParseBool("Smaller TP Targeting", cfg_SmallerTPTargeting);
    ParseNumber("TP FOV Radius", cfg_TPFOVRadius);
    ParseNumber("Actor Teleport Offset", cfg_ActorTeleportOffset);
    ParseNumber("TP No Target Distance", cfg_TPNoTargetDistance);

    // Gamemode settings
    ParseNumber("Incapacitate All Key", cfg_IncapacitateAllKey);
    ParseNumber("Instant Win Key", cfg_InstantWinKey);
    ParseNumber("Instant Lose Key", cfg_InstantLoseKey);
    ParseNumber("Arrest All Key", cfg_ArrestAllKey);
    ParseNumber("Report All Key", cfg_ReportAllKey);
    ParseNumber("Collect All Evidence Key", cfg_CollectAllEvidenceKey);

    // General ESP settings
    ParseBool("Enable FOV Circle", cfg_DrawFOVCircle);
    ParseBool("Enable ESP Boxes", cfg_DrawESPBoxes);
    ParseBool("Enable ESP Names", cfg_DrawESPNames);
    ParseBool("Enable ESP Health", cfg_DrawESPHealth);
    ParseBool("Enable ESP Bones", cfg_DrawESPBones);
    ParseBool("Enable ESP Lines", cfg_DrawESPLines);
    ParseBool("Enable Top ESP Lines", cfg_DrawESPLinesTop);
    
    // Player-specific ESP settings
    ParseBool("Enable Player ESP", cfg_DrawPlayerESP);
    ParseBool("Enable Player Boxes", cfg_DrawPlayerBoxes);
    ParseBool("Enable Player Names", cfg_DrawPlayerNames);
    ParseBool("Enable Player Health", cfg_DrawPlayerHealth);
    ParseBool("Enable Player Bones", cfg_DrawPlayerBones);
    ParseBool("Enable Player Lines", cfg_DrawPlayerLines);
    ParseBool("Enable Top Player Lines", cfg_DrawPlayerLinesTop);
    
    // AI Character ESP settings
    ParseBool("Enable SERT Red ESP", cfg_DrawSERTRedESP);
    ParseBool("Enable SERT Red Boxes", cfg_DrawSERTRedBoxes);
    ParseBool("Enable SERT Red Names", cfg_DrawSERTRedNames);
    ParseBool("Enable SERT Red Health", cfg_DrawSERTRedHealth);
    ParseBool("Enable SERT Red Bones", cfg_DrawSERTRedBones);
    ParseBool("Enable SERT Red Lines", cfg_DrawSERTRedLines);
    
    ParseBool("Enable SERT Blue ESP", cfg_DrawSERTBlueESP);
    ParseBool("Enable SERT Blue Boxes", cfg_DrawSERTBlueBoxes);
    ParseBool("Enable SERT Blue Names", cfg_DrawSERTBlueNames);
    ParseBool("Enable SERT Blue Health", cfg_DrawSERTBlueHealth);
    ParseBool("Enable SERT Blue Bones", cfg_DrawSERTBlueBones);
    ParseBool("Enable SERT Blue Lines", cfg_DrawSERTBlueLines);
    
    ParseBool("Enable Suspect ESP", cfg_DrawSuspectESP);
    ParseBool("Enable Suspect Boxes", cfg_DrawSuspectBoxes);
    ParseBool("Enable Suspect Names", cfg_DrawSuspectNames);
    ParseBool("Enable Suspect Health", cfg_DrawSuspectHealth);
    ParseBool("Enable Suspect Bones", cfg_DrawSuspectBones);
    ParseBool("Enable Suspect Lines", cfg_DrawSuspectLines);
    
    ParseBool("Enable Civilian ESP", cfg_DrawCivilianESP);
    ParseBool("Enable Civilian Boxes", cfg_DrawCivilianBoxes);
    ParseBool("Enable Civilian Names", cfg_DrawCivilianNames);
    ParseBool("Enable Civilian Health", cfg_DrawCivilianHealth);
    ParseBool("Enable Civilian Bones", cfg_DrawCivilianBones);
    ParseBool("Enable Civilian Lines", cfg_DrawCivilianLines);
    
    ParseBool("Enable Squad ESP", cfg_DrawSquadESP);
    ParseBool("Enable Squad Boxes", cfg_DrawSquadBoxes);
    ParseBool("Enable Squad Names", cfg_DrawSquadNames);
    ParseBool("Enable Squad Health", cfg_DrawSquadHealth);
    ParseBool("Enable Squad Bones", cfg_DrawSquadBones);
    ParseBool("Enable Squad Lines", cfg_DrawSquadLines);
    
    ParseBool("Enable Wounded ESP", cfg_DrawWoundedESP);
    ParseBool("Enable Wounded Boxes", cfg_DrawWoundedBoxes);
    ParseBool("Enable Wounded Names", cfg_DrawWoundedNames);
    ParseBool("Enable Wounded Health", cfg_DrawWoundedHealth);
    ParseBool("Enable Wounded Bones", cfg_DrawWoundedBones);
    ParseBool("Enable Wounded Lines", cfg_DrawWoundedLines);
    
    ParseNumber("Max AI ESP Distance", cfg_MaxAIESPDistance);

    // Object ESP settings
    ParseBool("Enable Evidence ESP", cfg_DrawEvidenceESP);
    ParseBool("Enable Collected Evidence ESP", cfg_DrawCollectedEvidenceESP);
    ParseBool("Enable Items ESP", cfg_DrawItemsESP);
    ParseBool("Enable Doors ESP", cfg_DrawDoorsESP);
    ParseBool("Enable Traps ESP", cfg_DrawTrapsESP);
    ParseBool("Enable Securables ESP", cfg_DrawSecurablesESP);
    ParseNumber("Max Object ESP Distance", cfg_MaxObjectESPDistance);

    // Debug settings
    ParseBool("Show Debug Class Names", cfg_ShowDebugClassNames);
    ParseBool("Show Debug Distance", cfg_ShowDebugDistance);
    ParseNumber("Debug Max Distance", cfg_DebugMaxDistance);

    ConfigLoaded = true;
}

void Configuration::Save() {
    EnsureDirectoryExists(configDirectory);

    std::ofstream configFile(configFilePath);
    if (configFile.is_open()) {
        configFile << "{\n";

        // Version
        configFile << "    \"Version\": " << Version << ",\n";

        // Window settings
        configFile << "    \"Menu Size X\": " << windowSizeX << ",\n";
        configFile << "    \"Menu Size Y\": " << windowSizeY << ",\n";

        // Visual settings
        configFile << "    \"Watermark\": " << (bShowWatermark ? "true" : "false") << ",\n";
        configFile << "    \"First Use\": " << (bFirstUse ? "true" : "false") << ",\n";
        configFile << "    \"Selected Theme\": " << selectedTheme << ",\n";
        configFile << "    \"Selected Language\": " << cfg_SelectedLanguage << ",\n";
        configFile << "    \"Show Spectators\": " << (bShowSpectators ? "true" : "false") << ",\n";
        configFile << "    \"FOV Circle Radius\": " << cfg_FOVRadius << ",\n";
        configFile << "    \"Circle Alpha\": " << cfg_CircleAlpha << ",\n";
        configFile << "    \"Loot Alpha\": " << cfg_LootAlpha << ",\n";
        configFile << "    \"ESP Thickness\": " << cfg_ESPThickness << ",\n";
        configFile << "    \"Max Player ESP Distance\": " << cfg_MaxPlayerESPDistance << ",\n";

        // Custom theme colors
        if (!customColors.empty()) {
            configFile << "    \"Custom Theme Colors\": {\n";
            bool first = true;
            for (const auto& pair : customColors) {
                if (!first) configFile << ",\n";
                first = false;

                const int colorIndex = pair.first;
                const ImVec4& color = pair.second;

                configFile << "        \"" << colorIndex << "\": {";
                configFile << "\"r\": " << color.x << ", ";
                configFile << "\"g\": " << color.y << ", ";
                configFile << "\"b\": " << color.z << ", ";
                configFile << "\"a\": " << color.w << "}";
            }
            configFile << "\n    },\n";
        }

        // Aimbot settings
        configFile << "    \"Aimbot FOV\": " << cfg_AimbotFOV << ",\n";
        configFile << "    \"Aimbot Smoothing\": " << cfg_AimbotSmoothing << ",\n";
        configFile << "    \"Aim Target\": " << cfg_AimTarget << ",\n";
        configFile << "    \"Aimbot Target Bone\": " << cfg_AimbotTargetBone << ",\n";
        configFile << "    \"Aimbot Box\": " << cfg_AimbotBox << ",\n";
        configFile << "    \"Aimbot Key\": " << cfg_AimbotKey << ",\n";
        configFile << "    \"Enable Aimbot\": " << (cfg_EnableAimbot ? "true" : "false") << ",\n";
        configFile << "    \"Enable Lootable Targeting\": " << (cfg_AllowOtherTargeting ? "true" : "false") << ",\n";
        configFile << "    \"Enable Silent Aimbot\": " << (cfg_SilentAimbotEnabled ? "true" : "false") << ",\n";
        configFile << "    \"Enable Visibility Check\": " << (cfg_AimVisCheck ? "true" : "false") << ",\n";
        configFile << "    \"Enable No-Spread\": " << (cfg_AimbotNoSpread ? "true" : "false") << ",\n";
        configFile << "    \"Enable No-Recoil\": " << (cfg_AimbotNoRecoil ? "true" : "false") << ",\n";
        configFile << "    \"Enable No-Sway\": " << (cfg_AimbotNoSway ? "true" : "false") << ",\n";

        // Weapon settings
        configFile << "    \"Enable Infinite Ammo\": " << (cfg_InfiniteAmmo ? "true" : "false") << ",\n";
        configFile << "    \"Enable Instant Reload\": " << (cfg_InstantReload ? "true" : "false") << ",\n";
        configFile << "    \"Ammo Amount\": " << cfg_CustomAmmoCount << ",\n";

        // Movement settings
        configFile << "    \"Enable NoClip\": " << (cfg_EnableNoClip ? "true" : "false") << ",\n";
        configFile << "    \"NoClip Previous\": " << (cfg_PreviousNoclipState ? "true" : "false") << ",\n";
        configFile << "    \"Enable Speedhack\": " << (cfg_EnableSpeedhack ? "true" : "false") << ",\n";
        configFile << "    \"Enable Infinite Stamina\": " << (cfg_DoUnlimitedStamina ? "true" : "false") << ",\n";
        configFile << "    \"Speedhack Amount\": " << cfg_speedPlayerValue << ",\n";
        configFile << "    \"Speedhack Key\": " << cfg_SpeedKey << ",\n";
        configFile << "    \"NoClip Key\": " << cfg_NoClipKey << ",\n";

        // Player settings
        configFile << "    \"Enable No Flash\": " << (cfg_DoNoFlash ? "true" : "false") << ",\n";
        configFile << "    \"Enable No Weight\": " << (cfg_DoNoWeight ? "true" : "false") << ",\n";
        configFile << "    \"Enable No Stagger\": " << (cfg_NoStagger ? "true" : "false") << ",\n";
        configFile << "    \"Enable Unlock All Items\": " << (cfg_UnlockAllItems ? "true" : "false") << ",\n";
        configFile << "    \"Enable Godmode\": " << (cfg_EnableGodmode ? "true" : "false") << ",\n";
        configFile << "    \"No Suspect Firefight\": " << (cfg_NoSuspectFirefight ? "true" : "false") << ",\n";
        configFile << "    \"Disarm All Suspects\": " << (cfg_DisarmAllSuspects ? "true" : "false") << ",\n";
        configFile << "    \"Force Suspect Surrender\": " << (cfg_ForceSuspectSurrender ? "true" : "false") << ",\n";
        configFile << "    \"Auto-Comply Suspects\": " << (cfg_AutoComplySuspects ? "true" : "false") << ",\n";
        configFile << "    \"Disable All Traps\": " << (cfg_DisableAllTraps ? "true" : "false") << ",\n";

        // Name Changer
        configFile << "    \"Player Name Input\": \"" << cfg_PlayerNameInput << "\",\n";

        // FOV settings
        configFile << "    \"Enable Custom FOV\": " << (cfg_EnableCustomFOV ? "true" : "false") << ",\n";
        configFile << "    \"Custom FOV Value\": " << cfg_CustomFOV << ",\n";

        // Unlit mode settings
        configFile << "    \"Enable Unlit Mode\": " << (cfg_EnableUnlitMode ? "true" : "false") << ",\n";

        // Teleport settings
        configFile << "    \"Enable Teleport To Target\": " << (cfg_TeleportToTarget ? "true" : "false") << ",\n";
        configFile << "    \"Teleport Key\": " << cfg_TeleportKey << ",\n";
        configFile << "    \"Teleport Method\": " << cfg_TeleportMethod << ",\n";
        
        // Unified Teleport settings
        configFile << "    \"Enable Unified Teleport\": " << (cfg_EnableTPTarget ? "true" : "false") << ",\n";
        configFile << "    \"Unified Teleport Key\": " << cfg_TPTargetKey << ",\n";
        configFile << "    \"Smaller TP Targeting\": " << (cfg_SmallerTPTargeting ? "true" : "false") << ",\n";
        configFile << "    \"TP FOV Radius\": " << cfg_TPFOVRadius << ",\n";
        configFile << "    \"Actor Teleport Offset\": " << cfg_ActorTeleportOffset << ",\n";
        configFile << "    \"TP No Target Distance\": " << cfg_TPNoTargetDistance << ",\n";

        // Gamemode settings
        configFile << "    \"Incapacitate All Key\": " << cfg_IncapacitateAllKey << ",\n";
        configFile << "    \"Instant Win Key\": " << cfg_InstantWinKey << ",\n";
        configFile << "    \"Instant Lose Key\": " << cfg_InstantLoseKey << ",\n";
        configFile << "    \"Arrest All Key\": " << cfg_ArrestAllKey << ",\n";
        configFile << "    \"Report All Key\": " << cfg_ReportAllKey << ",\n";
        configFile << "    \"Collect All Evidence Key\": " << cfg_CollectAllEvidenceKey << ",\n";

        // General ESP settings
        configFile << "    \"Enable FOV Circle\": " << (cfg_DrawFOVCircle ? "true" : "false") << ",\n";
        configFile << "    \"Enable ESP Boxes\": " << (cfg_DrawESPBoxes ? "true" : "false") << ",\n";
        configFile << "    \"Enable ESP Names\": " << (cfg_DrawESPNames ? "true" : "false") << ",\n";
        configFile << "    \"Enable ESP Health\": " << (cfg_DrawESPHealth ? "true" : "false") << ",\n";
        configFile << "    \"Enable ESP Bones\": " << (cfg_DrawESPBones ? "true" : "false") << ",\n";
        configFile << "    \"Enable ESP Lines\": " << (cfg_DrawESPLines ? "true" : "false") << ",\n";
        configFile << "    \"Enable Top ESP Lines\": " << (cfg_DrawESPLinesTop ? "true" : "false") << ",\n";
        
        // Player-specific ESP settings
        configFile << "    \"Enable Player ESP\": " << (cfg_DrawPlayerESP ? "true" : "false") << ",\n";
        configFile << "    \"Enable Player Boxes\": " << (cfg_DrawPlayerBoxes ? "true" : "false") << ",\n";
        configFile << "    \"Enable Player Names\": " << (cfg_DrawPlayerNames ? "true" : "false") << ",\n";
        configFile << "    \"Enable Player Health\": " << (cfg_DrawPlayerHealth ? "true" : "false") << ",\n";
        configFile << "    \"Enable Player Bones\": " << (cfg_DrawPlayerBones ? "true" : "false") << ",\n";
        configFile << "    \"Enable Player Lines\": " << (cfg_DrawPlayerLines ? "true" : "false") << ",\n";
        configFile << "    \"Enable Top Player Lines\": " << (cfg_DrawPlayerLinesTop ? "true" : "false") << ",\n";
        
        // AI Character ESP settings
        configFile << "    \"Enable SERT Red ESP\": " << (cfg_DrawSERTRedESP ? "true" : "false") << ",\n";
        configFile << "    \"Enable SERT Red Boxes\": " << (cfg_DrawSERTRedBoxes ? "true" : "false") << ",\n";
        configFile << "    \"Enable SERT Red Names\": " << (cfg_DrawSERTRedNames ? "true" : "false") << ",\n";
        configFile << "    \"Enable SERT Red Health\": " << (cfg_DrawSERTRedHealth ? "true" : "false") << ",\n";
        configFile << "    \"Enable SERT Red Bones\": " << (cfg_DrawSERTRedBones ? "true" : "false") << ",\n";
        configFile << "    \"Enable SERT Red Lines\": " << (cfg_DrawSERTRedLines ? "true" : "false") << ",\n";
        
        configFile << "    \"Enable SERT Blue ESP\": " << (cfg_DrawSERTBlueESP ? "true" : "false") << ",\n";
        configFile << "    \"Enable SERT Blue Boxes\": " << (cfg_DrawSERTBlueBoxes ? "true" : "false") << ",\n";
        configFile << "    \"Enable SERT Blue Names\": " << (cfg_DrawSERTBlueNames ? "true" : "false") << ",\n";
        configFile << "    \"Enable SERT Blue Health\": " << (cfg_DrawSERTBlueHealth ? "true" : "false") << ",\n";
        configFile << "    \"Enable SERT Blue Bones\": " << (cfg_DrawSERTBlueBones ? "true" : "false") << ",\n";
        configFile << "    \"Enable SERT Blue Lines\": " << (cfg_DrawSERTBlueLines ? "true" : "false") << ",\n";
        
        configFile << "    \"Enable Suspect ESP\": " << (cfg_DrawSuspectESP ? "true" : "false") << ",\n";
        configFile << "    \"Enable Suspect Boxes\": " << (cfg_DrawSuspectBoxes ? "true" : "false") << ",\n";
        configFile << "    \"Enable Suspect Names\": " << (cfg_DrawSuspectNames ? "true" : "false") << ",\n";
        configFile << "    \"Enable Suspect Health\": " << (cfg_DrawSuspectHealth ? "true" : "false") << ",\n";
        configFile << "    \"Enable Suspect Bones\": " << (cfg_DrawSuspectBones ? "true" : "false") << ",\n";
        configFile << "    \"Enable Suspect Lines\": " << (cfg_DrawSuspectLines ? "true" : "false") << ",\n";
        
        configFile << "    \"Enable Civilian ESP\": " << (cfg_DrawCivilianESP ? "true" : "false") << ",\n";
        configFile << "    \"Enable Civilian Boxes\": " << (cfg_DrawCivilianBoxes ? "true" : "false") << ",\n";
        configFile << "    \"Enable Civilian Names\": " << (cfg_DrawCivilianNames ? "true" : "false") << ",\n";
        configFile << "    \"Enable Civilian Health\": " << (cfg_DrawCivilianHealth ? "true" : "false") << ",\n";
        configFile << "    \"Enable Civilian Bones\": " << (cfg_DrawCivilianBones ? "true" : "false") << ",\n";
        configFile << "    \"Enable Civilian Lines\": " << (cfg_DrawCivilianLines ? "true" : "false") << ",\n";
        
        configFile << "    \"Enable Squad ESP\": " << (cfg_DrawSquadESP ? "true" : "false") << ",\n";
        configFile << "    \"Enable Squad Boxes\": " << (cfg_DrawSquadBoxes ? "true" : "false") << ",\n";
        configFile << "    \"Enable Squad Names\": " << (cfg_DrawSquadNames ? "true" : "false") << ",\n";
        configFile << "    \"Enable Squad Health\": " << (cfg_DrawSquadHealth ? "true" : "false") << ",\n";
        configFile << "    \"Enable Squad Bones\": " << (cfg_DrawSquadBones ? "true" : "false") << ",\n";
        configFile << "    \"Enable Squad Lines\": " << (cfg_DrawSquadLines ? "true" : "false") << ",\n";
        
        configFile << "    \"Enable Wounded ESP\": " << (cfg_DrawWoundedESP ? "true" : "false") << ",\n";
        configFile << "    \"Enable Wounded Boxes\": " << (cfg_DrawWoundedBoxes ? "true" : "false") << ",\n";
        configFile << "    \"Enable Wounded Names\": " << (cfg_DrawWoundedNames ? "true" : "false") << ",\n";
        configFile << "    \"Enable Wounded Health\": " << (cfg_DrawWoundedHealth ? "true" : "false") << ",\n";
        configFile << "    \"Enable Wounded Bones\": " << (cfg_DrawWoundedBones ? "true" : "false") << ",\n";
        configFile << "    \"Enable Wounded Lines\": " << (cfg_DrawWoundedLines ? "true" : "false") << ",\n";
        
        configFile << "    \"Max AI ESP Distance\": " << cfg_MaxAIESPDistance << ",\n";

        // Object ESP settings
        configFile << "    \"Enable Evidence ESP\": " << (cfg_DrawEvidenceESP ? "true" : "false") << ",\n";
        configFile << "    \"Enable Collected Evidence ESP\": " << (cfg_DrawCollectedEvidenceESP ? "true" : "false") << ",\n";
        configFile << "    \"Enable Items ESP\": " << (cfg_DrawItemsESP ? "true" : "false") << ",\n";
        configFile << "    \"Enable Doors ESP\": " << (cfg_DrawDoorsESP ? "true" : "false") << ",\n";
        configFile << "    \"Enable Traps ESP\": " << (cfg_DrawTrapsESP ? "true" : "false") << ",\n";
        configFile << "    \"Enable Securables ESP\": " << (cfg_DrawSecurablesESP ? "true" : "false") << ",\n";
        configFile << "    \"Max Object ESP Distance\": " << cfg_MaxObjectESPDistance << ",\n";

        // Debug settings
        configFile << "    \"Show Debug Class Names\": " << (cfg_ShowDebugClassNames ? "true" : "false") << ",\n";
        configFile << "    \"Show Debug Distance\": " << (cfg_ShowDebugDistance ? "true" : "false") << ",\n";
        configFile << "    \"Debug Max Distance\": " << cfg_DebugMaxDistance << "\n";

        configFile << "}";

        configFile.close();
    }
}

void Configuration::ApplyCustomTheme() {
    ImGuiStyle* style = &ImGui::GetStyle();
    style->GrabRounding = 4.0f;

    // Apply custom colors from the customColors map
    for (const auto& it : customColors) {
        int idx = it.first;
        const ImVec4& color = it.second;

        // Ensure the index is within valid ImGuiCol range
        if (idx >= 0 && idx < ImGuiCol_COUNT) {
            style->Colors[idx] = color;
        }
    }
}