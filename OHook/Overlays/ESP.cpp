#include "ESP.h"
#include "Configuration.h"
#include "ActorCache.h"
#include "Utils.h"
#include "SDKExt.h"
#include "ImGuiExt.h"
#include "ReadyornotOverlay.h"
#include "PlayerFeatures.h"
#include <OverlayBase.h>
#include <imgui_internal.h>
#include <Fonts.h>
#include <Windows.h>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <chrono>

using namespace SDK;

extern ImU32 PlayerESPColorVisible;
extern ImU32 PlayerESPColorNonVisible;
extern ImU32 PlayerESPColorAimed;
extern ImU32 SERTRedESPColor;
extern ImU32 SERTBlueESPColor;
extern ImU32 SuspectESPColor;
extern ImU32 CivilianESPColor;
extern ImU32 SquadESPColor;

namespace ReadyornotESP {

    void DrawGuiFOVCircle() {
        if (!Configuration::cfg_DrawFOVCircle)
            return;

        if (IsLevelTransitioning.load()) {
            return;
        }

        ReadyornotOverlay* Overlay = static_cast<ReadyornotOverlay*>(OverlayBase::Instance);
        if (!Overlay)
            return;

        APlayerController* PlayerController = GetARONPC();
        if (!PlayerController || !PlayerController->K2_GetPawn())
            return;

        FVector2D FOVCenter = { ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f };
        if (FOVCenter.X <= 0 || FOVCenter.Y <= 0)
            return;

        auto drawList = ImGui::GetBackgroundDrawList();
        if (!drawList)
            return;

        const ImU32 CircleColor = IM_COL32(0xFF, 0xFF, 0xFF, static_cast<int>(Configuration::cfg_CircleAlpha * 255));
        drawList->AddCircle(ImVec2(FOVCenter.X, FOVCenter.Y), Configuration::cfg_FOVRadius, CircleColor, 1200, 1.0f);

        const float FOVRadius = Configuration::cfg_FOVRadius;

        if (Overlay->BestTargetActor) {
            FVector2D TargetScreenPosition;
            if (PlayerController->ProjectWorldLocationToScreen(Overlay->BestTargetLocation, &TargetScreenPosition, true)) {
                float DistanceToCenter = CustomMath::Sqrt(
                    CustomMath::Square(TargetScreenPosition.X - FOVCenter.X) +
                    CustomMath::Square(TargetScreenPosition.Y - FOVCenter.Y)
                );

                if (DistanceToCenter <= FOVRadius) {
                    drawList->AddLine(
                        ImVec2(FOVCenter.X, FOVCenter.Y),
                        ImVec2(TargetScreenPosition.X, TargetScreenPosition.Y),
                        CircleColor,
                        Configuration::cfg_ESPThickness
                    );
                }
            }
        }
    }

    void DrawGuiESP() {
        if (!Configuration::cfg_DrawPlayerESP && 
            !Configuration::cfg_DrawSERTRedESP && 
            !Configuration::cfg_DrawSERTBlueESP && 
            !Configuration::cfg_DrawSuspectESP && 
            !Configuration::cfg_DrawCivilianESP && 
            !Configuration::cfg_DrawSquadESP &&
            !Configuration::cfg_DrawWoundedESP &&
            !Configuration::cfg_DrawEvidenceESP &&
            !Configuration::cfg_DrawCollectedEvidenceESP &&
            !Configuration::cfg_DrawItemsESP &&
            !Configuration::cfg_DrawDoorsESP &&
            !Configuration::cfg_DrawTrapsESP)
        {
            return;
        }

        if (IsLevelTransitioning.load()) {
            return;
        }

        auto PlayerController = GetARONPC();
        if (!PlayerController || !IsActorValid(PlayerController)) return;

        auto PawnPlayer = PlayerController->K2_GetPawn();
        if (!PawnPlayer || !IsActorValid(PawnPlayer)) return;

        const auto drawList = ImGui::GetBackgroundDrawList();
        if (!drawList) return;

        ImVec2 canvasSize = ImGui::GetIO().DisplaySize;

        const auto& allActors = ActorCache::GetInstance().GetCachedActors();

        // ================================
        //        DRAW CHARACTER ESP
        // ================================
        ReadyornotOverlay* Overlay = static_cast<ReadyornotOverlay*>(OverlayBase::Instance);
    
        for (const auto& actorInfo : allActors)
        {
            if (!actorInfo.Actor || !IsActorValid(actorInfo.Actor))
                continue;

            bool espEnabled = false;
            switch (actorInfo.Category) {
                case EActorCategory::Player:
                    espEnabled = Configuration::cfg_DrawPlayerESP;
                    break;
                case EActorCategory::SERT_Red:
                    espEnabled = Configuration::cfg_DrawSERTRedESP;
                    break;
                case EActorCategory::SERT_Blue:
                    espEnabled = Configuration::cfg_DrawSERTBlueESP;
                    break;
                case EActorCategory::Suspect:
                    espEnabled = Configuration::cfg_DrawSuspectESP;
                    break;
                case EActorCategory::Civilian:
                    espEnabled = Configuration::cfg_DrawCivilianESP;
                    break;
                case EActorCategory::Squad:
                    espEnabled = Configuration::cfg_DrawSquadESP;
                    break;
                case EActorCategory::Wounded:
                    espEnabled = Configuration::cfg_DrawWoundedESP;
                    break;
                case EActorCategory::Evidence:
                    espEnabled = Configuration::cfg_DrawEvidenceESP;
                    break;
                case EActorCategory::CollectedEvidence:
                    espEnabled = Configuration::cfg_DrawCollectedEvidenceESP;
                    break;
                case EActorCategory::Items:
                    espEnabled = Configuration::cfg_DrawItemsESP;
                    break;
                case EActorCategory::Doors:
                    espEnabled = Configuration::cfg_DrawDoorsESP;
                    break;
                case EActorCategory::DoorTraps:
                    espEnabled = Configuration::cfg_DrawTrapsESP;
                    break;
                case EActorCategory::Unknown:
                    espEnabled = Configuration::cfg_DrawSuspectESP;
                    break;
                default:
                    continue; // Skip unknown
            }

            if (!espEnabled)
                continue;

            // Handle different actor types
            bool isCharacter = (actorInfo.Category == EActorCategory::Player ||
                               actorInfo.Category == EActorCategory::SERT_Red ||
                               actorInfo.Category == EActorCategory::SERT_Blue ||
                               actorInfo.Category == EActorCategory::Suspect ||
                               actorInfo.Category == EActorCategory::Civilian ||
                               actorInfo.Category == EActorCategory::Squad ||
                               actorInfo.Category == EActorCategory::Wounded ||
                               actorInfo.Category == EActorCategory::Unknown);

            if (isCharacter) {
                auto* Character = static_cast<SDK::AReadyOrNotCharacter*>(actorInfo.Actor);
                if (!Character || !IsActorValid(Character))
                    continue;

            if (!Character->CharacterHealth || !IsComponentValid(Character->CharacterHealth) || 
                Character->GetHealthStatus() == EPlayerHealthStatus::HS_Dead || Character == PawnPlayer)
                continue;

            if (actorInfo.Category == EActorCategory::Player && Character == PawnPlayer)
                continue;

            FVector CharacterLocation = Character->K2_GetActorLocation();
            float distance = GetDistance3D(CharacterLocation, PawnPlayer->K2_GetActorLocation()) / 100.0f;
            float maxDistance = (actorInfo.Category == EActorCategory::Player) 
                ? Configuration::cfg_MaxPlayerESPDistance / 100.0f
                : Configuration::cfg_MaxAIESPDistance / 100.0f;
        
            if (distance > maxDistance)
                continue;

            USkeletalMeshComponent* MeshComponent = Character->Mesh;
            if (!MeshComponent || !IsComponentValid(MeshComponent)) continue;

            FVector Origin = CharacterLocation;
            FVector BoxExtent;
            float SphereRadius;
            UKismetSystemLibrary::GetComponentBounds(MeshComponent, &Origin, &BoxExtent, &SphereRadius);
            
            Origin = CharacterLocation;

            FVector ActorTop = Origin + FVector(0.0f, 0.0f, BoxExtent.Z);
            FVector ActorBottom = Origin - FVector(0.0f, 0.0f, BoxExtent.Z);

            FVector2D screenPosTop, screenPosBottom;
            if (!PlayerController->ProjectWorldLocationToScreen(ActorTop, &screenPosTop, true) ||
                !PlayerController->ProjectWorldLocationToScreen(ActorBottom, &screenPosBottom, true))
            {
                continue;
            }

            float boxHeight = screenPosBottom.Y - screenPosTop.Y;
            float boxWidth = boxHeight / 2.0f;

            const float ScalingFactor = 1.0f + (distance / (maxDistance * 100.0f));
            boxWidth *= ScalingFactor;
            boxHeight *= ScalingFactor;

            ImVec2 boxTopLeft = { static_cast<float>(screenPosTop.X - boxWidth / 2.0f), static_cast<float>(screenPosTop.Y) };
            ImVec2 boxBottomRight = { static_cast<float>(screenPosTop.X + boxWidth / 2.0f), static_cast<float>(screenPosBottom.Y) };

            if (boxTopLeft.x < 0.0f || boxTopLeft.y < 0.0f ||
                boxBottomRight.x > static_cast<float>(canvasSize.x) || boxBottomRight.y > static_cast<float>(canvasSize.y))
            {
                continue;
            }

            ImU32 boxColor;
            bool bIsVisible = Configuration::cfg_AimVisCheck
                ? PlayerController->LineOfSightTo(Character, PawnPlayer->K2_GetActorLocation(), false)
                : true;

            switch (actorInfo.Category) {
                case EActorCategory::Player:
                    boxColor = bIsVisible ? PlayerESPColorVisible : PlayerESPColorNonVisible;
                    break;
                case EActorCategory::SERT_Red:
                    boxColor = SERTRedESPColor;
                    break;
                case EActorCategory::SERT_Blue:
                    boxColor = SERTBlueESPColor;
                    break;
                case EActorCategory::Suspect:
                    boxColor = SuspectESPColor;
                    break;
                case EActorCategory::Civilian:
                    boxColor = CivilianESPColor;
                    break;
                case EActorCategory::Squad:
                    boxColor = SquadESPColor;
                    break;
                case EActorCategory::Wounded:
                    boxColor = WoundedESPColor;
                    break;
                case EActorCategory::Unknown:
                    boxColor = SuspectESPColor;
                    break;
                default:
                    boxColor = PlayerESPColorVisible;
                    break;
            }

            if (Overlay->BestTargetActor == actorInfo.Actor)
            {
                boxColor = PlayerESPColorAimed;
            }

            bool shouldDrawBoxes = false;
            
            switch (actorInfo.Category) {
                case EActorCategory::Player:
                    shouldDrawBoxes = Configuration::cfg_DrawPlayerBoxes;
                    break;
                case EActorCategory::SERT_Red:
                    shouldDrawBoxes = Configuration::cfg_DrawSERTRedBoxes;
                    break;
                case EActorCategory::SERT_Blue:
                    shouldDrawBoxes = Configuration::cfg_DrawSERTBlueBoxes;
                    break;
                case EActorCategory::Suspect:
                    shouldDrawBoxes = Configuration::cfg_DrawSuspectBoxes;
                    break;
                case EActorCategory::Civilian:
                    shouldDrawBoxes = Configuration::cfg_DrawCivilianBoxes;
                    break;
                case EActorCategory::Squad:
                    shouldDrawBoxes = Configuration::cfg_DrawSquadBoxes;
                    break;
                case EActorCategory::Wounded:
                    shouldDrawBoxes = Configuration::cfg_DrawWoundedBoxes;
                    break;
                default:
                    break;
            }

            // Draw box
            if (shouldDrawBoxes) {
                float boxThickness = Configuration::cfg_ESPThickness;

                switch (Configuration::cfg_AimbotBox) {
                case 0: // 2D Box
                    drawList->AddRect(
                        boxTopLeft,
                        boxBottomRight,
                        boxColor,
                        0.0f,
                        0,
                        boxThickness
                    );
                    break;

                case 1: // 2D Cornered Box
                    default: {
                        float cornerSize = boxWidth / 5.0f;

                        // Top Left
                        drawList->AddLine(
                            boxTopLeft,
                            ImVec2(boxTopLeft.x + cornerSize, boxTopLeft.y),
                            boxColor, boxThickness
                        );
                        drawList->AddLine(
                            boxTopLeft,
                            ImVec2(boxTopLeft.x, boxTopLeft.y + cornerSize),
                            boxColor, boxThickness
                        );

                        // Top Right
                        ImVec2 topRight = ImVec2(boxBottomRight.x, boxTopLeft.y);
                        drawList->AddLine(
                            topRight,
                            ImVec2(topRight.x - cornerSize, topRight.y),
                            boxColor, boxThickness
                        );
                        drawList->AddLine(
                            topRight,
                            ImVec2(topRight.x, topRight.y + cornerSize),
                            boxColor, boxThickness
                        );

                        // Bottom Left
                        ImVec2 bottomLeft = ImVec2(boxTopLeft.x, boxBottomRight.y);
                        drawList->AddLine(
                            bottomLeft,
                            ImVec2(bottomLeft.x + cornerSize, bottomLeft.y),
                            boxColor, boxThickness
                        );
                        drawList->AddLine(
                            bottomLeft,
                            ImVec2(bottomLeft.x, bottomLeft.y - cornerSize),
                            boxColor, boxThickness
                        );

                        // Bottom Right
                        ImVec2 bottomRight = boxBottomRight;
                        drawList->AddLine(
                            bottomRight,
                            ImVec2(bottomRight.x - cornerSize, bottomRight.y),
                            boxColor, boxThickness
                        );
                        drawList->AddLine(
                            bottomRight,
                            ImVec2(bottomRight.x, bottomRight.y - cornerSize),
                            boxColor, boxThickness
                        );
                        break;
                    }
                }
            }

            bool shouldDrawHealth = false;
            switch (actorInfo.Category) {
                case EActorCategory::Player:
                    shouldDrawHealth = Configuration::cfg_DrawPlayerHealth;
                    break;
                case EActorCategory::SERT_Red:
                    shouldDrawHealth = Configuration::cfg_DrawSERTRedHealth;
                    break;
                case EActorCategory::SERT_Blue:
                    shouldDrawHealth = Configuration::cfg_DrawSERTBlueHealth;
                    break;
                case EActorCategory::Suspect:
                    shouldDrawHealth = Configuration::cfg_DrawSuspectHealth;
                    break;
                case EActorCategory::Civilian:
                    shouldDrawHealth = Configuration::cfg_DrawCivilianHealth;
                    break;
                case EActorCategory::Squad:
                    shouldDrawHealth = Configuration::cfg_DrawSquadHealth;
                    break;
                case EActorCategory::Wounded:
                    shouldDrawHealth = Configuration::cfg_DrawWoundedHealth;
                    break;
                default:
                    break;
            }

            // Health bar
            if (shouldDrawHealth) {
                if (Character->CharacterHealth && IsComponentValid(Character->CharacterHealth))
                {
                    float currentHealth = Character->GetCurrentHealth();
                    float maxHealth = Character->GetMaxHealth();

                    if (maxHealth > 0.0f && currentHealth >= 0.0f)
                    {
                        float healthBarHeight = boxHeight * (currentHealth / maxHealth);
                        float barWidth = 3.0f;

                        ImVec2 barTopLeft = { boxTopLeft.x - barWidth - 2, boxTopLeft.y };
                        ImVec2 barBottomRight = { barTopLeft.x + barWidth, boxBottomRight.y };
                        ImVec2 barFillTop = { barTopLeft.x, boxBottomRight.y - healthBarHeight };
                        ImVec2 barFillBottom = { barBottomRight.x, boxBottomRight.y };

                        // Background
                        drawList->AddRectFilled(barTopLeft, barBottomRight, IM_COL32(0, 0, 0, 255));
                        // Fill
                        drawList->AddRectFilled(
                            barFillTop,
                            barFillBottom,
                            (currentHealth > maxHealth * 0.5f)
                            ? IM_COL32(0x00, 0xFF, 0x00, 0xFF)  // green
                            : IM_COL32(0xFF, 0xA5, 0x00, 0xFF)  // orange
                        );
                    }
                }
            }

            bool shouldDrawNames = false;
            switch (actorInfo.Category) {
                case EActorCategory::Player:
                    shouldDrawNames = Configuration::cfg_DrawPlayerNames;
                    break;
                case EActorCategory::SERT_Red:
                    shouldDrawNames = Configuration::cfg_DrawSERTRedNames;
                    break;
                case EActorCategory::SERT_Blue:
                    shouldDrawNames = Configuration::cfg_DrawSERTBlueNames;
                    break;
                case EActorCategory::Suspect:
                    shouldDrawNames = Configuration::cfg_DrawSuspectNames;
                    break;
                case EActorCategory::Civilian:
                    shouldDrawNames = Configuration::cfg_DrawCivilianNames;
                    break;
                case EActorCategory::Squad:
                    shouldDrawNames = Configuration::cfg_DrawSquadNames;
                    break;
                case EActorCategory::Wounded:
                    shouldDrawNames = Configuration::cfg_DrawWoundedNames;
                    break;
                default:
                    break;
            }

            // Name + distance
            if (shouldDrawNames) {
                ImVec2 centerBottom = {
                    (boxTopLeft.x + boxBottomRight.x) / 2.0f,
                    boxBottomRight.y + 5.0f
                };

                std::string characterNameText = actorInfo.CharacterName;

                // Add distance
                char distanceBuffer[32];
                sprintf_s(distanceBuffer, " [%.0fm]", distance);
                std::string displayText = characterNameText + std::string(distanceBuffer);

                if (drawList && OverlayBase::Instance->ESPFont) {
                    ImVec2 nameTextSize = ImGui::CalcTextSize(displayText.c_str());
                    ImVec2 namePos = {
                        centerBottom.x - nameTextSize.x / 2.0f,
                        centerBottom.y
                    };
                    namePos.y = std::clamp(namePos.y, 4.0f, static_cast<float>(canvasSize.y) - 15.0f);

                    drawTextOutlined(drawList, namePos, boxColor, displayText.c_str(), OverlayBase::Instance->ESPFont);
                }
            }

            bool shouldDrawLines = false;
            switch (actorInfo.Category) {
                case EActorCategory::Player:
                    shouldDrawLines = Configuration::cfg_DrawPlayerLines;
                    break;
                case EActorCategory::SERT_Red:
                    shouldDrawLines = Configuration::cfg_DrawSERTRedLines;
                    break;
                case EActorCategory::SERT_Blue:
                    shouldDrawLines = Configuration::cfg_DrawSERTBlueLines;
                    break;
                case EActorCategory::Suspect:
                    shouldDrawLines = Configuration::cfg_DrawSuspectLines;
                    break;
                case EActorCategory::Civilian:
                    shouldDrawLines = Configuration::cfg_DrawCivilianLines;
                    break;
                case EActorCategory::Squad:
                    shouldDrawLines = Configuration::cfg_DrawSquadLines;
                    break;
                case EActorCategory::Wounded:
                    shouldDrawLines = Configuration::cfg_DrawWoundedLines;
                    break;
                default:
                    break;
            }

            // Player lines
            if (shouldDrawLines && drawList) {
                ImVec2 screenCenter = {
                    static_cast<float>(canvasSize.x) / 2.0f,
                    Configuration::cfg_DrawPlayerLinesTop ? 0.0f : static_cast<float>(canvasSize.y)
                };
                ImVec2 lineEnd = Configuration::cfg_DrawPlayerLinesTop
                    ? ImVec2(static_cast<float>(screenPosTop.X), static_cast<float>(screenPosTop.Y))
                    : ImVec2(static_cast<float>(screenPosBottom.X), static_cast<float>(screenPosBottom.Y));

                drawList->AddLine(screenCenter, lineEnd, boxColor, Configuration::cfg_ESPThickness);
            }

            bool shouldDrawBones = false;
            switch (actorInfo.Category) {
                case EActorCategory::Player:
                    shouldDrawBones = Configuration::cfg_DrawPlayerBones;
                    break;
                case EActorCategory::SERT_Red:
                    shouldDrawBones = Configuration::cfg_DrawSERTRedBones;
                    break;
                case EActorCategory::SERT_Blue:
                    shouldDrawBones = Configuration::cfg_DrawSERTBlueBones;
                    break;
                case EActorCategory::Suspect:
                    shouldDrawBones = Configuration::cfg_DrawSuspectBones;
                    break;
                case EActorCategory::Civilian:
                    shouldDrawBones = Configuration::cfg_DrawCivilianBones;
                    break;
                case EActorCategory::Squad:
                    shouldDrawBones = Configuration::cfg_DrawSquadBones;
                    break;
                case EActorCategory::Wounded:
                    shouldDrawBones = Configuration::cfg_DrawWoundedBones;
                    break;
                default:
                    break;
            }

            // Skeleton
            if (shouldDrawBones) {
                static SDK::FName aSkeleton[][2] =
                {
                    { SDK::UKismetStringLibrary::Conv_StringToName(L"Hips"), SDK::UKismetStringLibrary::Conv_StringToName(L"Spine")},
                    { SDK::UKismetStringLibrary::Conv_StringToName(L"Spine"), SDK::UKismetStringLibrary::Conv_StringToName(L"Neck")},
                
                    { SDK::UKismetStringLibrary::Conv_StringToName(L"Neck"), SDK::UKismetStringLibrary::Conv_StringToName(L"RightShoulder")},
                    { SDK::UKismetStringLibrary::Conv_StringToName(L"Neck"), SDK::UKismetStringLibrary::Conv_StringToName(L"LeftShoulder")},
               
                    { SDK::UKismetStringLibrary::Conv_StringToName(L"RightShoulder"), SDK::UKismetStringLibrary::Conv_StringToName(L"RightArm")},
                    { SDK::UKismetStringLibrary::Conv_StringToName(L"RightArm"), SDK::UKismetStringLibrary::Conv_StringToName(L"RightForeArm")},
                    { SDK::UKismetStringLibrary::Conv_StringToName(L"RightForeArm"), SDK::UKismetStringLibrary::Conv_StringToName(L"RightHand")},

                    { SDK::UKismetStringLibrary::Conv_StringToName(L"LeftShoulder"), SDK::UKismetStringLibrary::Conv_StringToName(L"LeftArm")},    
                    { SDK::UKismetStringLibrary::Conv_StringToName(L"LeftArm"), SDK::UKismetStringLibrary::Conv_StringToName(L"LeftForeArm")},    
                    { SDK::UKismetStringLibrary::Conv_StringToName(L"LeftForeArm"), SDK::UKismetStringLibrary::Conv_StringToName(L"LeftHand")},    
               
                    { SDK::UKismetStringLibrary::Conv_StringToName(L"Hips"), SDK::UKismetStringLibrary::Conv_StringToName(L"RightUpleg")},         
                    { SDK::UKismetStringLibrary::Conv_StringToName(L"RightUpleg"), SDK::UKismetStringLibrary::Conv_StringToName(L"RightLeg")},     
                    { SDK::UKismetStringLibrary::Conv_StringToName(L"RightLeg"), SDK::UKismetStringLibrary::Conv_StringToName(L"RightFoot")},            
                    { SDK::UKismetStringLibrary::Conv_StringToName(L"Hips"), SDK::UKismetStringLibrary::Conv_StringToName(L"LeftUpLeg")},         
                    { SDK::UKismetStringLibrary::Conv_StringToName(L"LeftUpLeg"), SDK::UKismetStringLibrary::Conv_StringToName(L"LeftLeg")},     
                    { SDK::UKismetStringLibrary::Conv_StringToName(L"LeftLeg"), SDK::UKismetStringLibrary::Conv_StringToName(L"LeftFoot")},      
                    { SDK::UKismetStringLibrary::Conv_StringToName(L"Neck"), SDK::UKismetStringLibrary::Conv_StringToName(L"Head")},              
                };

                for (auto& bonePair : aSkeleton) {
                    FVector BoneStartLocation = MeshComponent->GetSocketLocation(bonePair[0]);
                    FVector BoneEndLocation = MeshComponent->GetSocketLocation(bonePair[1]);

                    FVector2D boneStart, boneEnd;
                    if (!BoneStartLocation.IsZero() &&
                        !BoneEndLocation.IsZero() &&
                        PlayerController->ProjectWorldLocationToScreen(BoneStartLocation, &boneStart, true) &&
                        PlayerController->ProjectWorldLocationToScreen(BoneEndLocation, &boneEnd, true))
                    {
                        drawList->AddLine(ImVec2(boneStart.X, boneStart.Y),
                            ImVec2(boneEnd.X, boneEnd.Y),
                            boxColor, Configuration::cfg_ESPThickness);
                    }
                }
            }
            } else {
                // Handle object rendering
                DrawObjectESP(actorInfo, PlayerController, PawnPlayer, drawList, canvasSize);
            }
        }

        // --- DEBUG CLASS NAMES ---
        if (Configuration::cfg_ShowDebugClassNames) {

            if (IsLevelTransitioning.load()) {
                return;
            }
            
            UWorld* GWorld = UWorld::GetWorld();
            if (GWorld && GWorld->Levels.IsValid()) {
                FVector PlayerLocation = PawnPlayer->K2_GetActorLocation();
                
                for (int i = 0; i < GWorld->Levels.Num(); ++i) {
                    if (!GWorld->Levels.IsValidIndex(i))
                        continue;

                    const auto Level = GWorld->Levels[i];
                    if (!Level)
                        continue;

                    for (int j = 0; j < Level->Actors.Num(); ++j) {
                        const auto Actor = Level->Actors[j];
                        if (!Actor || !IsActorValid(Actor))
                            continue;
                            
                        if (Actor == PawnPlayer)
                            continue;
                            
                        float Distance = PawnPlayer->GetDistanceTo(Actor) / 100.0f; // Converted to meters
                        
                        if (Distance > Configuration::cfg_DebugMaxDistance / 100.0f)
                            continue;

                        FVector ActorLocation = Actor->K2_GetActorLocation();
                        FVector2D ScreenPos;
                        if (!PlayerController->ProjectWorldLocationToScreen(ActorLocation, &ScreenPos, true))
                            continue;

                        std::string className = Actor->Class ? Actor->Class->GetName() : "Unknown";
                        std::string displayText = className;

                        if (Configuration::cfg_ShowDebugDistance) {
                            char distanceBuffer[32];
                            sprintf_s(distanceBuffer, "[%.0fm]", Distance);
                            displayText += " " + std::string(distanceBuffer);
                        }
                        
                        ImU32 debugColor = IM_COL32(255, 255, 0, 180); // Yellowish
                        
                        // Draw classname
                        if (drawList && OverlayBase::Instance->ESPFont) {
                            ImVec2 NameSize = ImGui::CalcTextSize(displayText.c_str(), nullptr, true);
                            ImVec2 NamePos = {
                                static_cast<float>(ScreenPos.X) - NameSize.x / 2.0f,
                                static_cast<float>(ScreenPos.Y) + 10.0f
                            };

                            if (NamePos.x >= 0 && NamePos.y >= 0 && 
                                NamePos.x < static_cast<float>(canvasSize.x) && NamePos.y < static_cast<float>(canvasSize.y)) {
                                drawTextOutlined(drawList, NamePos, debugColor, displayText.c_str(), OverlayBase::Instance->ESPFont);
                            }
                        }
                    }
                }
            }
        }
    }

    void DrawObjectESP(const CachedActorInfo& actorInfo, SDK::APlayerController* PlayerController, SDK::AActor* PawnPlayer, 
                       ImDrawList* drawList, ImVec2 canvasSize) {
        
        FVector ObjectLocation = actorInfo.Actor->K2_GetActorLocation();
        float distance = GetDistance3D(ObjectLocation, PawnPlayer->K2_GetActorLocation()) / 100.0f;
        if (distance > Configuration::cfg_MaxObjectESPDistance / 100.0f)
            return;

        FVector2D screenPos;
        if (!PlayerController->ProjectWorldLocationToScreen(ObjectLocation, &screenPos, true))
            return;

        if (screenPos.X < 0 || screenPos.Y < 0 || screenPos.X > canvasSize.x || screenPos.Y > canvasSize.y)
            return;

        ImU32 objectColor = actorInfo.Color;

        // Draw text
        if (drawList && OverlayBase::Instance->ESPFont) {
            std::string displayText = actorInfo.CharacterName;
            if (Configuration::cfg_ShowDebugDistance) {
                char distanceBuffer[32];
                sprintf_s(distanceBuffer, " [%.0fm]", distance);
                displayText += std::string(distanceBuffer);
            }

            ImVec2 textSize = ImGui::CalcTextSize(displayText.c_str());
            ImVec2 textPos = {
                static_cast<float>(screenPos.X) - textSize.x / 2.0f,
                static_cast<float>(screenPos.Y) - textSize.y / 2.0f
            };

            textPos.x = std::clamp(textPos.x, 4.0f, static_cast<float>(canvasSize.x) - textSize.x - 4.0f);
            textPos.y = std::clamp(textPos.y, 4.0f, static_cast<float>(canvasSize.y) - textSize.y - 4.0f);

            drawTextOutlined(drawList, textPos, objectColor, displayText.c_str(), OverlayBase::Instance->ESPFont);
        }
    }

    bool IsValidScreenPosition(const ImVec2& position, const ImVec2& canvasSize) {
        return position.x >= 0.0f && position.y >= 0.0f && position.x <= canvasSize.x && position.y <= canvasSize.y;
    }

} // namespace ReadyornotESP
