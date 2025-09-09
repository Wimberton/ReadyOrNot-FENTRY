#pragma once
#include <string>
#include <type_traits>
#include <fstream>
#include <imgui.h>
#include <filesystem>
#include <iostream>
#include <map>

class ReadyornotOverlay;

class Configuration final {
private:
    static bool ReadJsonFile();
    static void ParseBool(std::string Key, bool& Var);
    static void ParseBool(std::string Key, bool& Var, bool DefaultValue);
    static void ParseString(std::string Key, char* Var, size_t MaxLength);

    template<typename T>
    static void ParseNumber(std::string Key, T& Var);

    static std::string JsonConfigFile;
    static bool ConfigLoaded;

public:
    static void Load(ReadyornotOverlay* Overlay);
    static void Save();
    static void ApplyCustomTheme();

#pragma region ConfigVars

    // Config Version
    static int Version;
    
    // Window settings
    static float windowSizeX;
    static float windowSizeY;
    
    static bool bFirstUse;
    static int selectedTheme;
    static int cfg_SelectedLanguage;
    static std::map<int, ImVec4> customColors;

    // Visual settings
    static bool bShowWatermark;
    static bool bShowSpectators;
    static float cfg_FOVRadius;
    static float cfg_CircleAlpha;
    static float cfg_LootAlpha;
    static float cfg_ESPThickness;
    static float cfg_MaxPlayerESPDistance;
    
    // Aimbot settings
    static bool cfg_EnableAimbot;
    static bool cfg_AllowOtherTargeting;
    static bool cfg_SilentAimbotEnabled;
    static bool cfg_AimVisCheck;
    static bool cfg_AimbotNoSpread;
    static bool cfg_AimbotNoRecoil;
    static bool cfg_AimbotNoSway;
    static float cfg_AimbotFOV;
    static float cfg_AimbotSmoothing;
    static int cfg_AimbotTargetBone;
    static int cfg_AimbotBox;
    static int cfg_AimbotKey;
    static int cfg_AimTarget;
    
    // Weapon settings
    static bool cfg_InfiniteAmmo;
    static bool cfg_InstantReload;
    static int cfg_CustomAmmoCount;
    
    // Movement settings
    static bool cfg_EnableNoClip;
    static bool cfg_PreviousNoclipState;
    static bool cfg_EnableSpeedhack;
    static bool cfg_DoUnlimitedStamina;
    static float cfg_speedPlayerValue;
    static int cfg_SpeedKey;
    static int cfg_NoClipKey;
    
    // Player settings
    static bool cfg_DoNoFlash;
    static bool cfg_DoNoWeight;
    static bool cfg_NoStagger;
    static bool cfg_UnlockAllItems;
    static bool cfg_EnableGodmode;
    static bool cfg_NoSuspectFirefight;
    static bool cfg_DisarmAllSuspects;
    static bool cfg_ForceSuspectSurrender;
    static bool cfg_AutoComplySuspects;
    
    // Trap settings
    static bool cfg_DisableAllTraps;

    // Teleport settings
    static bool cfg_TeleportToTarget;
    static int cfg_TeleportKey;
    static int cfg_TeleportMethod;
    
    // Unified Teleport settings
    static bool cfg_EnableTPTarget;
    static int cfg_TPTargetKey;
    static bool cfg_SmallerTPTargeting;
    static float cfg_TPFOVRadius;
    static float cfg_ActorTeleportOffset;
    static float cfg_TPNoTargetDistance;

    // Gamemode settings
    static int cfg_IncapacitateAllKey;
    static int cfg_InstantWinKey;
    static int cfg_InstantLoseKey;
    static int cfg_ArrestAllKey;
    static int cfg_ReportAllKey;
    static int cfg_CollectAllEvidenceKey;
    
    // General ESP settings (affect all character types)
    static bool cfg_DrawFOVCircle;
    static bool cfg_DrawESPBoxes;
    static bool cfg_DrawESPNames;
    static bool cfg_DrawESPHealth;
    static bool cfg_DrawESPBones;
    static bool cfg_DrawESPLines;
    static bool cfg_DrawESPLinesTop;
    
    // Player-specific ESP settings
    static bool cfg_DrawPlayerESP;
    static bool cfg_DrawPlayerBoxes;
    static bool cfg_DrawPlayerNames;
    static bool cfg_DrawPlayerHealth;
    static bool cfg_DrawPlayerBones;
    static bool cfg_DrawPlayerLines;
    static bool cfg_DrawPlayerLinesTop;
    
    // AI Character ESP settings
    static bool cfg_DrawSERTRedESP;
    static bool cfg_DrawSERTRedBoxes;
    static bool cfg_DrawSERTRedNames;
    static bool cfg_DrawSERTRedHealth;
    static bool cfg_DrawSERTRedBones;
    static bool cfg_DrawSERTRedLines;
    
    static bool cfg_DrawSERTBlueESP;
    static bool cfg_DrawSERTBlueBoxes;
    static bool cfg_DrawSERTBlueNames;
    static bool cfg_DrawSERTBlueHealth;
    static bool cfg_DrawSERTBlueBones;
    static bool cfg_DrawSERTBlueLines;
    
    static bool cfg_DrawSuspectESP;
    static bool cfg_DrawSuspectBoxes;
    static bool cfg_DrawSuspectNames;
    static bool cfg_DrawSuspectHealth;
    static bool cfg_DrawSuspectBones;
    static bool cfg_DrawSuspectLines;
    
    static bool cfg_DrawCivilianESP;
    static bool cfg_DrawCivilianBoxes;
    static bool cfg_DrawCivilianNames;
    static bool cfg_DrawCivilianHealth;
    static bool cfg_DrawCivilianBones;
    static bool cfg_DrawCivilianLines;
    
    static bool cfg_DrawSquadESP;
    static bool cfg_DrawSquadBoxes;
    static bool cfg_DrawSquadNames;
    static bool cfg_DrawSquadHealth;
    static bool cfg_DrawSquadBones;
    static bool cfg_DrawSquadLines;
    
    static bool cfg_DrawWoundedESP;
    static bool cfg_DrawWoundedBoxes;
    static bool cfg_DrawWoundedNames;
    static bool cfg_DrawWoundedHealth;
    static bool cfg_DrawWoundedBones;
    static bool cfg_DrawWoundedLines;
    
    static float cfg_MaxAIESPDistance;

    // Object ESP settings
    static bool cfg_DrawEvidenceESP;
    static bool cfg_DrawCollectedEvidenceESP;
    static bool cfg_DrawItemsESP;
    static bool cfg_DrawDoorsESP;
    static bool cfg_DrawTrapsESP;
    static bool cfg_DrawSecurablesESP;
    static float cfg_MaxObjectESPDistance;

    // Debug settings
    static bool cfg_ShowDebugClassNames;
    static bool cfg_ShowDebugDistance;
    static float cfg_DebugMaxDistance;

    // Name Changer
    static char cfg_PlayerNameInput[64];

    // FOV settings
    static bool cfg_EnableCustomFOV;
    static float cfg_CustomFOV;

    // Unlit mode settings
    static bool cfg_EnableUnlitMode;

#pragma endregion
};