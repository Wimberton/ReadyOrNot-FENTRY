#pragma once

#include "ActorCache.h"
#include "Configuration.h"
#include "SDKExt.h"
#include <OverlayBase.h>
#include <map>
#include <imgui.h>
#include <SDK.hpp>
#include <chrono>
#include <unordered_map>

using namespace SDK;

#define NO_HOTKEY -1
#define FENTRY_IsKeyPressed(key) GetAsyncKeyState(key) & 1 && GetAsyncKeyState(key) & 0x8000
#define FENTRY_IsKeyHeld(key) (GetAsyncKeyState(key) & 0x8000)

struct SimpleLootableInfo {
    FString DisplayName;
    FLinearColor Color;
};

struct SimpleLootableMapping {
    FString LootableName;
    SimpleLootableInfo Info;
    bool* ConfigFlag;
};

extern bool waitingForKey;
extern bool waitingForTeleportKey;
extern bool waitingForUnifiedTeleportKey;
extern bool waitingForSpeedKey;
extern bool waitingForNoClipKey;
extern bool waitingForExfiltrationKey;
extern bool waitingForAutoLootKey;
extern bool waitingForIncapacitateKey;
extern bool waitingForInstantWinKey;
extern bool waitingForInstantLoseKey;
extern bool waitingForArrestAllKey;
extern bool waitingForReportAllKey;
extern bool waitingForCollectAllEvidenceKey;

extern const char* boneTargets[];
extern const char* espBoxStyles[];
extern int selectedBoxStyle;

constexpr int BOX_STYLES_COUNT = 2;
constexpr int BONE_TARGETS_COUNT = 5;

extern bool toggleAllCommon;
extern bool toggleAllUncommon;
extern bool toggleAllRare;
extern bool toggleAllEpic;
extern bool toggleAllLegendary;

extern float tempPlayerColor[4];
extern float tempLootableColor[4];

class ReadyornotOverlay final : public OverlayBase {
protected:
    void DrawHUD() override;
    void DrawOverlay() override;
    void DrawGuiFOVCircle() override;
    void DrawGuiESP() override;

public:
    SDK::AActor* Aimbot_Target;

    UWorld* GWorld;
    UEngine* GEngine;
    ULocalPlayer* LocalPlayer;
    APlayerController* PlayerController;

    AReadyOrNotPlayerController* ARONPlayerController;
    AReadyOrNotCharacter* ARONPlayerCharacter;
    AReadyOrNotCharacter* LocalCharacter;
    ACharacter* ActorCharacter;

    SDK::UGameViewportClient* LocalView;

    bool bWaitingForKeyPress = false;

    int screenWidth;
    int screenHeight;

    int SpectatorCount = 0;
    float originalLadderSpeed = 3.1f;
    
    bool AimbotInUse = false;
    double SelectionThreshold = 50.0;
    
    double BestScore;
    double BestScoreOther;
    
    AActor* BestTargetActor = nullptr;
    FVector BestTargetLocation;
    FRotator BestTargetRotation;
    
    AActor* BestTargetOther = nullptr;
    FVector BestTargetOtherLocation;
    FRotator BestTargetOtherRotation;

    FName LockedBoneName;
    ULevel* CurrentLevel;
    std::string CurrentMap = "Unknown";
    std::string CurrentLevelName = "Unknown";

    bool getTheme = true;
    static const char* themes[4];
};