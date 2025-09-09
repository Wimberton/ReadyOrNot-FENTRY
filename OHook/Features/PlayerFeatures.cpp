#include <cmath>
#include <algorithm>
#include <iostream>
#include "Configuration.h"
#include "Utils.h"
#include "SDKExt.h"
#include "ReadyornotOverlay.h"
#include "PlayerFeatures.h"

#include <SDK/ReadyOrNot_parameters.hpp>

#include "console.hpp"
#include "LocalizationManager.h"
#include "ImGuiExt.h"
#include "ActorCache.h"
#include <chrono>
#include <Windows.h>
#include <imgui.h>
#include <map>
#include <atomic>

using namespace SDK;

namespace PlayerFeatures {

    void DoNoClip() {
        if (IsLevelTransitioning.load()) {
            return;
        }
        
        static bool wasNoClipEnabled = false;

        auto RONCharacter = GetARONCharacter();
        if (!RONCharacter || !IsActorValid(RONCharacter)) {
            if (wasNoClipEnabled) {
                wasNoClipEnabled = false;
            }
            return;
        }

        AReadyOrNotPlayerController* PlayerController = GetARONPC();
        if (!PlayerController || !IsActorValid(PlayerController)) {
            if (wasNoClipEnabled) {
                wasNoClipEnabled = false;
            }
            return;
        }

        UCharacterMovementComponent* RONMovementComponent = RONCharacter->CharacterMovement;
        if (!RONMovementComponent || !IsComponentValid(RONMovementComponent) || RONMovementComponent->IsDefaultObject()) {
            if (wasNoClipEnabled) {
                wasNoClipEnabled = false;
            }
            return;
        }

        if (!RONCharacter->CapsuleComponent || !IsComponentValid(RONCharacter->CapsuleComponent)) {
            if (wasNoClipEnabled) {
                wasNoClipEnabled = false;
            }
            return;
        }

        if (!PlayerController->PlayerCameraManager || !IsActorValid(PlayerController->PlayerCameraManager)) {
            if (wasNoClipEnabled) {
                wasNoClipEnabled = false;
            }
            return;
        }

        if (Configuration::cfg_EnableNoClip && (Configuration::cfg_NoClipKey == 0 || GetAsyncKeyState(Configuration::cfg_NoClipKey) & 0x8000)) {
            if (!wasNoClipEnabled) {
                RONMovementComponent->SetMovementMode(EMovementMode::MOVE_Flying, 5);
                RONCharacter->CapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
                wasNoClipEnabled = true;
            }

            const FRotator& CameraRot = PlayerController->PlayerCameraManager->GetCameraRotation();

            FVector CameraForward = UKismetMathLibrary::GetForwardVector(CameraRot);
            FVector CameraRight = UKismetMathLibrary::GetRightVector(CameraRot);
            constexpr FVector CameraUp = { 0.f, 0.f, 1.f };

            CameraForward.Normalize();
            CameraRight.Normalize();

            FVector MovementDirection = { 0.f, 0.f, 0.f };
            float FlySpeed = 800.0f;

            if (IsKeyHeld('W')) {
                MovementDirection += CameraForward * FlySpeed;
            }
            if (IsKeyHeld('S')) {
                MovementDirection -= CameraForward * FlySpeed;
            }
            if (IsKeyHeld('D')) {
                MovementDirection += CameraRight * FlySpeed;
            }
            if (IsKeyHeld('A')) {
                MovementDirection -= CameraRight * FlySpeed;
            }
            if (IsKeyHeld(VK_SPACE)) {
                MovementDirection += CameraUp * FlySpeed;
            }
            if (IsKeyHeld(VK_CONTROL)) {
                MovementDirection -= CameraUp * FlySpeed;
            }
            if (IsKeyHeld(VK_SHIFT)) {
                FlySpeed *= 2.0f;
            }

            MovementDirection.Normalize();
            MovementDirection *= FlySpeed;

            constexpr float DeltaTime = 1.0f / 60.0f;

            const FVector MovementDelta = MovementDirection * DeltaTime;

            FHitResult HitResult;
            RONCharacter->K2_SetActorLocation(RONCharacter->K2_GetActorLocation() + MovementDelta, false, &HitResult, false);
        }
        else if (wasNoClipEnabled) {
            if (RONMovementComponent && IsComponentValid(RONMovementComponent) && !RONMovementComponent->IsDefaultObject()) {
                RONMovementComponent->SetMovementMode(EMovementMode::MOVE_Walking, 1);
            }
            
            if (RONCharacter && IsActorValid(RONCharacter) && 
                RONCharacter->CapsuleComponent && IsComponentValid(RONCharacter->CapsuleComponent)) {
                RONCharacter->CapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
                RONCharacter->CapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
            }

            wasNoClipEnabled = false;
        }
    }

    void DoSpeedmod() {
        if (IsLevelTransitioning.load()) {
            return;
        }
        
        static bool wasSpeedhackEnabled = false;

        auto RONCharacter = GetARONCharacter();
        if (!RONCharacter || !IsActorValid(RONCharacter)) {
            if (wasSpeedhackEnabled) {
                wasSpeedhackEnabled = false;
            }
            return;
        }

        APlayerController* PlayerController = GetARONPC();
        if (!PlayerController || !IsActorValid(PlayerController)) {
            if (wasSpeedhackEnabled) {
                wasSpeedhackEnabled = false;
            }
            return;
        }

        AActor* PawnPlayer = PlayerController->K2_GetPawn();
        if (!PawnPlayer || !IsActorValid(PawnPlayer)) {
            if (wasSpeedhackEnabled) {
                wasSpeedhackEnabled = false;
            }
            return;
        }

        if (Configuration::cfg_EnableSpeedhack && (Configuration::cfg_SpeedKey == 0 || GetAsyncKeyState(Configuration::cfg_SpeedKey) & 0x8000)) {
            float SpeedMultiplier = Configuration::cfg_speedPlayerValue;
            
            if (SpeedMultiplier > 0.1f && SpeedMultiplier <= 10.0f) {
                PawnPlayer->CustomTimeDilation = SpeedMultiplier;
                wasSpeedhackEnabled = true;
            }
        }
        else if (wasSpeedhackEnabled) {
            if (PawnPlayer && IsActorValid(PawnPlayer)) {
                PawnPlayer->CustomTimeDilation = 1.0f;
            }
            wasSpeedhackEnabled = false;
        }
    }

    void DoCustomFOV() {
        if (!Configuration::cfg_EnableCustomFOV)
            return;
            
        if (IsLevelTransitioning.load()) {
            return;
        }
        
        SetCustomFOV(Configuration::cfg_CustomFOV);
    }

    void DoGodmode() {
        if (!Configuration::cfg_EnableGodmode) {
            return;
        }
            
        if (IsLevelTransitioning.load()) {
            return;
        }
            
        auto RONCharacter = GetARONCharacter();
        if (!RONCharacter || !IsActorValid(RONCharacter)) {
            return;
        }

        RONCharacter->bCanBeDamaged = false;
            
        UCharacterHealthComponent* HealthComponent = RONCharacter->CharacterHealth;
        if (!HealthComponent || !IsComponentValid(HealthComponent) || HealthComponent->IsDefaultObject()) {
            return;
        }

        const float godmodeHealth = 9999.0f;
        const int32 maxTickets = 100;

        ELimbType limbs[] = {
            ELimbType::LT_Head,
            ELimbType::LT_RightLeg,
            ELimbType::LT_LeftLeg,
            ELimbType::LT_RightArm,
            ELimbType::LT_LeftArm
        };

        for (const auto& limbType : limbs) {
            try {
                auto* limbDataPtr = &HealthComponent->Head;
                
                switch (limbType) {
                    case ELimbType::LT_Head:
                        limbDataPtr = &HealthComponent->Head;
                        break;
                    case ELimbType::LT_RightLeg:
                        limbDataPtr = &HealthComponent->RightLeg;
                        break;
                    case ELimbType::LT_LeftLeg:
                        limbDataPtr = &HealthComponent->LeftLeg;
                        break;
                    case ELimbType::LT_RightArm:
                        limbDataPtr = &HealthComponent->RightArm;
                        break;
                    case ELimbType::LT_LeftArm:
                        limbDataPtr = &HealthComponent->LeftArm;
                        break;
                }

                float* healthPtr = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(limbDataPtr) + 0x8);
                float* maxHealthPtr = reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(limbDataPtr) + 0xC);
                int32* ticketsPtr = reinterpret_cast<int32*>(reinterpret_cast<uintptr_t>(limbDataPtr) + 0x20);
                int32* maxTicketsPtr = reinterpret_cast<int32*>(reinterpret_cast<uintptr_t>(limbDataPtr) + 0x1C);

                *healthPtr = godmodeHealth;
                *maxHealthPtr = godmodeHealth;
                *ticketsPtr = maxTickets;
                *maxTicketsPtr = maxTickets;

                HealthComponent->SetLimbHealth(limbType, godmodeHealth);
                HealthComponent->IncreaseLimbHealth(limbType, godmodeHealth);
                HealthComponent->ResetLimbTickets(limbType);
                HealthComponent->IncreaseLimbTickets(limbType, maxTickets);
                HealthComponent->SetCurrentLimbHealthToMax(limbType);
            }
            catch (...) {
            }
        }

        if (HealthComponent->GetHealthStatus() != EPlayerHealthStatus::HS_Healthy) {
            HealthComponent->SetHealthStatus(EPlayerHealthStatus::HS_Healthy);
        }

        if (RONCharacter->IsIncapacitated() || RONCharacter->IsDeadOrUnconscious() || RONCharacter->IsDowned()) {
            HealthComponent->SetHealthStatus(EPlayerHealthStatus::HS_Healthy);
        }

        HealthComponent->ResetReviveHealth();
        HealthComponent->SetReviveHealth(godmodeHealth);
        HealthComponent->SetRemainingRevives(maxTickets);
        HealthComponent->IncreaseRevive();
        HealthComponent->IncreaseReviveHealth(godmodeHealth);
    }

    void DisableGodmode() {
        auto RONCharacter = GetARONCharacter();
        if (!RONCharacter || !IsActorValid(RONCharacter)) {
            return;
        }

        RONCharacter->bCanBeDamaged = true;
    }

    void DoNoSuspectFirefight() {
        if (!Configuration::cfg_NoSuspectFirefight)
            return;

        if (IsLevelTransitioning.load()) {
            return;
        }

        const auto& allActors = ActorCache::GetInstance().GetCachedActors();
        
        for (const auto& actorInfo : allActors) {
            if (actorInfo.Category != EActorCategory::Suspect)
                continue;
                
            if (!actorInfo.Actor || !IsActorValid(actorInfo.Actor))
                continue;
                
            auto* CyberneticChar = static_cast<SDK::ACyberneticCharacter*>(actorInfo.Actor);
            if (!CyberneticChar || !IsActorValid(CyberneticChar))
                continue;
                
            if (!CyberneticChar->CharacterHealth || 
                !IsComponentValid(CyberneticChar->CharacterHealth) || 
                CyberneticChar->GetHealthStatus() == SDK::EPlayerHealthStatus::HS_Dead)
                continue;
                
            if (CyberneticChar->CombatState != SDK::ECombatState::CS_Unaware) {
                CyberneticChar->CombatState = SDK::ECombatState::CS_Unaware;
            }
        }
    }

    void DoDisarmAllSuspects() {
        if (!Configuration::cfg_DisarmAllSuspects)
            return;

        if (IsLevelTransitioning.load()) {
            return;
        }

        const auto& allActors = ActorCache::GetInstance().GetCachedActors();
        
        for (const auto& actorInfo : allActors) {
            if (actorInfo.Category != EActorCategory::Suspect)
                continue;
                
            if (!actorInfo.Actor || !IsActorValid(actorInfo.Actor))
                continue;
                
            auto* CyberneticChar = static_cast<SDK::ACyberneticCharacter*>(actorInfo.Actor);
            if (!CyberneticChar || !IsActorValid(CyberneticChar))
                continue;
                
            if (!CyberneticChar->CharacterHealth || 
                !IsComponentValid(CyberneticChar->CharacterHealth) || 
                CyberneticChar->GetHealthStatus() == SDK::EPlayerHealthStatus::HS_Dead)
                continue;
                
            CyberneticChar->bDrawingWeapon = false;
            CyberneticChar->bPickingUpWeapon = false;
            CyberneticChar->bIsRaisingWeapon = false;
            CyberneticChar->bIsLoweringWeapon = false;
            
            CyberneticChar->DrawingWeaponTime = 0.0f;
            CyberneticChar->PickingUpWeaponTime = 0.0f;
            CyberneticChar->RaisingWeaponTime = 0.0f;
            CyberneticChar->LoweringWeaponTime = 0.0f;
        }
    }

    void DoForceSuspectSurrender() {
        if (!Configuration::cfg_ForceSuspectSurrender)
            return;

        if (IsLevelTransitioning.load()) {
            return;
        }

        const auto& allActors = ActorCache::GetInstance().GetCachedActors();
        
        for (const auto& actorInfo : allActors) {
            if (actorInfo.Category != EActorCategory::Suspect)
                continue;
                
            if (!actorInfo.Actor || !IsActorValid(actorInfo.Actor))
                continue;
                
            auto* CyberneticChar = static_cast<SDK::ACyberneticCharacter*>(actorInfo.Actor);
            if (!CyberneticChar || !IsActorValid(CyberneticChar))
                continue;
                
            if (!CyberneticChar->CharacterHealth || 
                !IsComponentValid(CyberneticChar->CharacterHealth) || 
                CyberneticChar->GetHealthStatus() == SDK::EPlayerHealthStatus::HS_Dead)
                continue;
                
            if (!CyberneticChar->IsComplying()) {
                CyberneticChar->bIsComplying = true;
                
                CyberneticChar->Surrender();
                
                CyberneticChar->ForceComplianceStrength = 1.0f;
                
                CyberneticChar->CombatState = SDK::ECombatState::CS_Unaware;
                
                CyberneticChar->bIsFakeSurrender = false;
            }
        }
    }

    void DoAutoComplySuspects() {
        if (!Configuration::cfg_AutoComplySuspects)
            return;

        if (IsLevelTransitioning.load()) {
            return;
        }

        const auto& allActors = ActorCache::GetInstance().GetCachedActors();
        
        for (const auto& actorInfo : allActors) {
            if (actorInfo.Category != EActorCategory::Suspect &&
                actorInfo.Category != EActorCategory::Civilian)
                continue;
                
            if (!actorInfo.Actor || !IsActorValid(actorInfo.Actor))
                continue;
                
            auto* CyberneticChar = static_cast<SDK::ACyberneticCharacter*>(actorInfo.Actor);
            if (!CyberneticChar || !IsActorValid(CyberneticChar))
                continue;
                
            if (!CyberneticChar->CharacterHealth || 
                !IsComponentValid(CyberneticChar->CharacterHealth) || 
                CyberneticChar->GetHealthStatus() == SDK::EPlayerHealthStatus::HS_Dead)
                continue;
                
            CyberneticChar->ForceComplianceStrength = 1.0f;
            
            CyberneticChar->bIsComplying = true;
            
            CyberneticChar->bIsWaiting = true;
            
            CyberneticChar->CombatState = SDK::ECombatState::CS_Unaware;
            
            CyberneticChar->Stress = 0.0f;
            
            CyberneticChar->HesitationTime = 0.0f;
            
            CyberneticChar->bIsFakeSurrender = false;
        }
    }

    void DoDisableAllTraps() {
        if (!Configuration::cfg_DisableAllTraps)
            return;

        if (IsLevelTransitioning.load()) {
            return;
        }

        const auto& allActors = ActorCache::GetInstance().GetCachedActors();
        
        for (const auto& actorInfo : allActors) {
            if (actorInfo.Category != EActorCategory::DoorTraps)
                continue;
                
            if (!actorInfo.Actor || !IsActorValid(actorInfo.Actor))
                continue;
                
            auto* TrapActor = static_cast<SDK::ATrapActor*>(actorInfo.Actor);
            if (!TrapActor || !IsActorValid(TrapActor))
                continue;
                
            if (TrapActor->TrapStatus != SDK::ETrapState::TS_Disabled) {
                TrapActor->TrapStatus = SDK::ETrapState::TS_Disabled;
                
                TrapActor->TrapDeInit();
            }
        }
    }
}
