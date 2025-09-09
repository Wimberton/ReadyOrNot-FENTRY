#include "AimFeatures.h"
#include "ActorCache.h"
#include "Utils.h"
#include "console.hpp"
#include <chrono>
#include <algorithm>
#include <unordered_map>
#include <Windows.h>

using namespace SDK;

namespace AimFeatures {

    void DoTargeting(ReadyornotOverlay* Overlay, const SDK::AHUD* HUD)
    {
        if (!Configuration::cfg_EnableAimbot || !Overlay || !HUD || !HUD->Canvas)
            return;

        if (IsLevelTransitioning.load()) {
            return;
        }

        const auto PlayerController = GetARONPC();
        if (!PlayerController || !IsActorValid(PlayerController))
            return;

        const auto RONCharacter = GetARONCharacter();
        if (!RONCharacter || !IsActorValid(RONCharacter))
            return;

        FVector CharacterLocation = RONCharacter->K2_GetActorLocation();

        AActor* PawnPlayer = PlayerController->K2_GetPawn();
        if (!PawnPlayer || !IsActorValid(PawnPlayer))
            return;

        AReadyOrNotCharacter* LocalCharacter = static_cast<AReadyOrNotCharacter*>(PawnPlayer);
        if (!LocalCharacter || !IsActorValid(LocalCharacter))
            return;

        if (!PlayerController->PlayerCameraManager || !IsActorValid(PlayerController->PlayerCameraManager))
            return;
            
        FVector ViewPoint = PlayerController->PlayerCameraManager->GetCameraLocation();

        float ScreenWidth = HUD->Canvas->SizeX;
        float ScreenHeight = HUD->Canvas->SizeY;
        FVector2D FOVCenter = { ScreenWidth * 0.5f, ScreenHeight * 0.5f };

        double BestScore = DBL_MAX;
        double BestScoreOther = DBL_MAX;
        bool HasValidTarget = false;
        bool HasValidOtherTarget = false;

        AActor* CurrentBestTarget = nullptr;
        FVector BestBoneLocation;

        AActor* CurrentBestOtherTarget = nullptr;
        FVector BestOtherLocation;

        // Weight constants
        const double AngleWeight = 0.15;
        const double DistanceWeight = 0.05;
        const double MovementWeight = 0.05;

        const auto& allActors = ActorCache::GetInstance().GetCachedActors();

        for (const auto& actorInfo : allActors)
        {
            if (!actorInfo.Actor || !IsActorValid(actorInfo.Actor))
                continue;

            FVector ActorLocation = actorInfo.Actor->K2_GetActorLocation();
            FVector2D TargetScreenPosition;
            if (!PlayerController->ProjectWorldLocationToScreen(ActorLocation, &TargetScreenPosition, true))
                continue;

            float ScreenDistance = CustomMath::Sqrt(
                CustomMath::Square(TargetScreenPosition.X - FOVCenter.X) +
                CustomMath::Square(TargetScreenPosition.Y - FOVCenter.Y)
            );
            if (ScreenDistance > Configuration::cfg_FOVRadius)
                continue;

            bool shouldTarget = false;
            float maxDistance = Configuration::cfg_MaxPlayerESPDistance / 100.0f;
            
            switch (actorInfo.Category) {
                case EActorCategory::Player:
                    shouldTarget = false;
                    maxDistance = Configuration::cfg_MaxPlayerESPDistance / 100.0f;
                    break;
                case EActorCategory::Suspect:
                    shouldTarget = Configuration::cfg_DrawSuspectESP;
                    maxDistance = Configuration::cfg_MaxAIESPDistance / 100.0f;
                    break;
                case EActorCategory::SERT_Red:
                    shouldTarget = false;
                    maxDistance = Configuration::cfg_MaxAIESPDistance / 100.0f;
                    break;
                case EActorCategory::SERT_Blue:
                    shouldTarget = false;
                    maxDistance = Configuration::cfg_MaxAIESPDistance / 100.0f;
                    break;
                case EActorCategory::Civilian:
                    shouldTarget = false;
                    maxDistance = Configuration::cfg_MaxAIESPDistance / 100.0f;
                    break;
                case EActorCategory::Squad:
                    shouldTarget = false;
                    break;
                default:
                    shouldTarget = false;
                    break;
            }
            
            if (!shouldTarget)
                continue;

            AReadyOrNotCharacter* Character = static_cast<AReadyOrNotCharacter*>(actorInfo.Actor);
            if (!Character || !IsActorValid(Character))
                continue;

            if (Character == LocalCharacter || !Character->CharacterHealth || Character->GetHealthStatus() == EPlayerHealthStatus::HS_Dead)
                continue;

            float Distance = Character->GetDistanceTo(RONCharacter) / 100.0f;
            if (Distance > maxDistance)
                continue;

            if (Configuration::cfg_AimVisCheck && !PlayerController->LineOfSightTo(Character, ViewPoint, false))
                continue;

            FRotator ViewRotation = PlayerController->GetControlRotation();
            FVector ForwardVector = UKismetMathLibrary::GetForwardVector(ViewRotation);
            FVector DirectionToTarget = (ActorLocation - CharacterLocation).GetNormalized();
            double Angle = CustomMath::RadiansToDegrees(acosf(static_cast<float>(ForwardVector.Dot(DirectionToTarget))));

            FVector TargetVelocity = Character->GetVelocity();
            FVector RelativeVelocity = TargetVelocity - RONCharacter->GetVelocity();
            FVector RelativeDirection = RelativeVelocity.GetNormalized();

            // Bone logic
            FVector EvaluatedBoneLocation = ActorLocation;
            USkeletalMeshComponent* Mesh = Character->Mesh;

            if (Mesh && IsComponentValid(Mesh) && !Mesh->IsDefaultObject())
            {
                try {
                    FName selectedBoneName = GetSelectedBoneName(Configuration::cfg_AimbotTargetBone);
                    FVector boneLocation = Mesh->GetSocketLocation(selectedBoneName);
                
                    if (!boneLocation.IsZero())
                    {
                        EvaluatedBoneLocation = boneLocation;
                    }
                }
                catch (...) {
                    // Silently handle errors
                }
            }

            // Weighted scoring
            double Score =
                (AngleWeight * Angle) +
                (DistanceWeight * Distance) +
                (MovementWeight * RelativeDirection.Magnitude());

            if (Angle <= Configuration::cfg_FOVRadius / 2.0 && Score < BestScore)
            {
                BestScore = Score;
                CurrentBestTarget = Character;
                BestBoneLocation = EvaluatedBoneLocation;
                HasValidTarget = true;
            }
        }

        if (HasValidTarget)
        {
            Overlay->BestTargetActor = CurrentBestTarget;
            Overlay->BestScore = BestScore;
            Overlay->BestTargetLocation = BestBoneLocation;
            Overlay->BestTargetRotation = UKismetMathLibrary::FindLookAtRotation(CharacterLocation, BestBoneLocation);
        }
        else if (HasValidOtherTarget)
        {
            Overlay->BestTargetOther = CurrentBestOtherTarget;
            Overlay->BestScoreOther = BestScoreOther;
            Overlay->BestTargetOtherLocation = BestOtherLocation;
            Overlay->BestTargetOtherRotation = UKismetMathLibrary::FindLookAtRotation(CharacterLocation, BestOtherLocation);
        }
        else
        {
            Overlay->BestTargetActor = nullptr;
            Overlay->BestScore = DBL_MAX;
            Overlay->BestTargetLocation = FVector{0.0f, 0.0f, 0.0f};
            Overlay->BestTargetRotation = FRotator{0.0f, 0.0f, 0.0f};

            Overlay->BestTargetOther = nullptr;
            Overlay->BestScoreOther = DBL_MAX;
            Overlay->BestTargetOtherLocation = FVector{0.0f, 0.0f, 0.0f};
            Overlay->BestTargetOtherRotation = FRotator{0.0f, 0.0f, 0.0f};
        }
    }

    void DoAimbot(ReadyornotOverlay* Overlay, const SDK::AHUD* HUD) {
        if (!Configuration::cfg_EnableAimbot || !Overlay || !HUD || !HUD->Canvas)
            return;

        if (Overlay->ShowOverlay() || !IsGameWindowActive())
            return;

        if (IsLevelTransitioning.load()) {
            return;
        }

        const auto PlayerController = GetARONPC();
        if (!PlayerController || !IsActorValid(PlayerController))
            return;

        const auto RONCharacter = GetARONCharacter();
        if (!RONCharacter || !IsActorValid(RONCharacter))
            return;

        AActor* TargetActor = Overlay->BestTargetActor;
        if (!TargetActor || !IsActorValid(TargetActor))
            return;

        FVector BestTargetLocation = Overlay->BestTargetLocation;

        const auto CameraManager = PlayerController->PlayerCameraManager;
        if (!CameraManager || !IsActorValid(CameraManager))
            return;

        FVector CameraLocation = CameraManager->GetCameraLocation();
        FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(CameraLocation, BestTargetLocation);
        FRotator CurrentControlRotation = PlayerController->GetControlRotation();

        // Regular aimbot logic
        float SmoothingFactor = UKismetMathLibrary::Clamp(Configuration::cfg_AimbotSmoothing, 1.0f, 100.0f);
        bool bAimbotKeyHeld = (GetAsyncKeyState(Configuration::cfg_AimbotKey) & 0x8000) != 0;
        Overlay->AimbotInUse = bAimbotKeyHeld;

        AReadyOrNotCharacter* TargetPlayer = static_cast<AReadyOrNotCharacter*>(TargetActor);
        if (TargetPlayer && IsActorValid(TargetPlayer) && 
            TargetPlayer->Mesh && IsComponentValid(TargetPlayer->Mesh) && !TargetPlayer->Mesh->IsDefaultObject()) {
            if (!bAimbotKeyHeld)
                return;

            if (SmoothingFactor == 1.0f) {
                PlayerController->SetControlRotation(TargetRotation);
            }
            else {
                float InterpSpeed = UKismetMathLibrary::MapRangeClamped(SmoothingFactor, 1.0f, 100.0f, 25.0f, 1.0f);
                float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
                FRotator SmoothedRotation = UKismetMathLibrary::RInterpTo(CurrentControlRotation, TargetRotation, DeltaTime, InterpSpeed);

                PlayerController->SetControlRotation(SmoothedRotation);
            }
        }
    }

    void DoInfiniteAmmo() {
        if (!Configuration::cfg_InfiniteAmmo)
            return;

        if (IsLevelTransitioning.load()) {
            return;
        }

        auto RONCharacter = GetARONCharacter();
        if (!RONCharacter || !IsActorValid(RONCharacter))
            return;

        ABaseWeapon* CurrentWeapon = GetCurrentWeapon();
        if (!CurrentWeapon || !IsActorValid(CurrentWeapon)) {
            return;
        }

        static ABaseWeapon* LastProcessedWeapon = nullptr;
        if (LastProcessedWeapon != CurrentWeapon) {
            
            LastProcessedWeapon = CurrentWeapon;
            InvalidateWeaponCache();
            CurrentWeapon = GetCurrentWeapon();

            if (!CurrentWeapon || !IsActorValid(CurrentWeapon)) {
                return;
            }
        }

        ABaseMagazineWeapon* MagazineWeapon = static_cast<ABaseMagazineWeapon*>(CurrentWeapon);
        if (MagazineWeapon && IsActorValid(MagazineWeapon)) {
            try {
                TArray<FName> AmmoTypes;
                if (MagazineWeapon->AmmunitionTypes.Num() > 0) {
                    AmmoTypes = MagazineWeapon->AmmunitionTypes;
                }

                int32 maxMags = MagazineWeapon->MagazineCountMax;
                if (maxMags > 0) {
                    MagazineWeapon->SetMagazineCount(maxMags, AmmoTypes);
                }

                MagazineWeapon->ReplenishAmmo();
                
            } catch (...) {
                // Silently handle errors
            }
        }
    }

    void RemoveWeaponEffects() {
        if (!Configuration::cfg_AimbotNoSpread)
            return;

        if (IsLevelTransitioning.load()) {
            return;
        }

        static bool OriginalValuesSaved = false;
        static float OriginalSpreadValue;
        static float OriginalSpreadMin;
        static float OriginalSpreadMax;
        static float OriginalSpreadModValue1;
        static float OriginalSpreadModValue2;
        static float OriginalWobble;
        static float OriginalInitialWobbleDelay;
        static float OriginalMovementSpeedMultiplier;
        static ABaseWeapon* LastProcessedWeapon = nullptr;

        auto RONCharacter = GetARONCharacter();
        if (!RONCharacter || !IsActorValid(RONCharacter))
            return;

        ABaseWeapon* CurrentWeapon = GetCurrentWeapon();
        if (!CurrentWeapon || !IsActorValid(CurrentWeapon)) {
            return;
        }

        if (LastProcessedWeapon != CurrentWeapon) {
            LastProcessedWeapon = CurrentWeapon;
            OriginalValuesSaved = false;
        }

        try {
            if (!OriginalValuesSaved) {
                OriginalSpreadValue = CurrentWeapon->SpreadPattern.Pitch;
                OriginalSpreadMin = CurrentWeapon->SpreadPattern.Yaw;
                OriginalSpreadMax = CurrentWeapon->SpreadPattern.Roll;
                OriginalSpreadModValue1 = CurrentWeapon->FirstShotSpread;
                OriginalSpreadModValue2 = CurrentWeapon->ADSSpreadMultiplier;
                OriginalWobble = CurrentWeapon->Wobble;
                OriginalInitialWobbleDelay = CurrentWeapon->InitialWobbleDelay;
                OriginalMovementSpeedMultiplier = CurrentWeapon->MovementSpeedMultiplier;
                OriginalValuesSaved = true;
            }

            // no spread modifications
            if (Configuration::cfg_AimbotNoSpread) {
                CurrentWeapon->SpreadPattern.Pitch = 0.0f;
                CurrentWeapon->SpreadPattern.Yaw = 0.0f; 
                CurrentWeapon->SpreadPattern.Roll = 0.0f;
                CurrentWeapon->FirstShotSpread = 0.0f;
                CurrentWeapon->ADSSpreadMultiplier = 0.0f;
                CurrentWeapon->VelocitySpreadMultiplier = 0.0f;
                
                // pending spread zero
                CurrentWeapon->PendingSpread.Pitch = 0.0f;
                CurrentWeapon->PendingSpread.Yaw = 0.0f;
                CurrentWeapon->PendingSpread.Roll = 0.0f;
            }

            // no recoil modifications
            if (CurrentWeapon->RecoilPattern.Num() > 0) {
                for (int32 i = 0; i < CurrentWeapon->RecoilPattern.Num(); i++) {
                    CurrentWeapon->RecoilPattern[i].Pitch = 0.0f;
                    CurrentWeapon->RecoilPattern[i].Yaw = 0.0f;
                    CurrentWeapon->RecoilPattern[i].Roll = 0.0f;
                }
            }

            // recoil multipliers
            CurrentWeapon->ADSRecoilMultiplier = 0.0f;
            CurrentWeapon->RecoilMultiplierPitch = 0.0f;
            CurrentWeapon->RecoilMultiplierYaw = 0.0f;
            CurrentWeapon->FirstShotRecoil = 0.0f;
            CurrentWeapon->VelocityRecoilMultiplier = 0.0f;

            // procedural recoil
            CurrentWeapon->RecoilFireStrength = 0.0f;
            CurrentWeapon->RecoilFireStrengthFirst = 0.0f;
            CurrentWeapon->RecoilAngleStrength = 0.0f;
            CurrentWeapon->RecoilRandomness = 0.0f;

            // Clear recoil buildup
            CurrentWeapon->RecoilRotationBuildup.Pitch = 0.0f;
            CurrentWeapon->RecoilRotationBuildup.Yaw = 0.0f;
            CurrentWeapon->RecoilRotationBuildup.Roll = 0.0f;
            CurrentWeapon->RecoilPositionBuildup.X = 0.0f;
            CurrentWeapon->RecoilPositionBuildup.Y = 0.0f;
            CurrentWeapon->RecoilPositionBuildup.Z = 0.0f;

            // procedural recoil runtime
            CurrentWeapon->ProcRecoil_Trans.X = 0.0f;
            CurrentWeapon->ProcRecoil_Trans.Y = 0.0f;
            CurrentWeapon->ProcRecoil_Trans.Z = 0.0f;
            CurrentWeapon->ProcRecoil_Rot.Pitch = 0.0f;
            CurrentWeapon->ProcRecoil_Rot.Yaw = 0.0f;
            CurrentWeapon->ProcRecoil_Rot.Roll = 0.0f;
            CurrentWeapon->ProcRecoil_Trans_Buildup.X = 0.0f;
            CurrentWeapon->ProcRecoil_Trans_Buildup.Y = 0.0f;
            CurrentWeapon->ProcRecoil_Trans_Buildup.Z = 0.0f;
            CurrentWeapon->ProcRecoil_Rot_Buildup.Pitch = 0.0f;
            CurrentWeapon->ProcRecoil_Rot_Buildup.Yaw = 0.0f;
            CurrentWeapon->ProcRecoil_Rot_Buildup.Roll = 0.0f;

            // weapon sway and wobble effects
            CurrentWeapon->Wobble = 0.0f;
            CurrentWeapon->InitialWobbleDelay = 0.0f;

            // movement speed penalties
            CurrentWeapon->MovementSpeedMultiplier = 1.0f;

            // ADS modifiers for better handling
            CurrentWeapon->RecoilFireADSModifier = 0.0f;
            CurrentWeapon->RecoilAngleADSModifier = 0.0f;
            CurrentWeapon->RecoilBuildupADSModifier = 0.0f;

            // Improve weapon handling by removing delays and penalties
            CurrentWeapon->RefireDelay = 0.0f;
            CurrentWeapon->FirstShotResetTime = 0.0f;

            // recoil return settings 
            CurrentWeapon->RecoilReturnRate = 100.0f;
            CurrentWeapon->RecoilReturnPercentage = 1.0f;
            CurrentWeapon->RecoilReturnInterpSpeed = 100.0f;
            CurrentWeapon->SpreadReturnRate = 100.0f;

            // recoil interpolation and damping
            CurrentWeapon->RecoilInterpSpeed = 100.0f;
            CurrentWeapon->RecoilDampStrength = 0.0f;
            CurrentWeapon->RecoilBuildupDampStrength = 0.0f;

            // recoil buildup system
            CurrentWeapon->RecoilHasBuildup = false;

            // fire time effects
            CurrentWeapon->RecoilFireTime = 0.0f;

            if (!Configuration::cfg_AimbotNoSpread && OriginalValuesSaved) {
                CurrentWeapon->SpreadPattern.Pitch = OriginalSpreadValue;
                CurrentWeapon->SpreadPattern.Yaw = OriginalSpreadMin;
                CurrentWeapon->SpreadPattern.Roll = OriginalSpreadMax;
                CurrentWeapon->FirstShotSpread = OriginalSpreadModValue1;
                CurrentWeapon->ADSSpreadMultiplier = OriginalSpreadModValue2;
                CurrentWeapon->Wobble = OriginalWobble;
                CurrentWeapon->InitialWobbleDelay = OriginalInitialWobbleDelay;
                CurrentWeapon->MovementSpeedMultiplier = OriginalMovementSpeedMultiplier;
                OriginalValuesSaved = false;
            }

        } catch (...) {
            // Silently handle errors
        }
    }

} // namespace AimFeatures
