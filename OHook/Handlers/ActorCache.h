#pragma once

#include <vector>
#include <chrono>
#include <string>
#include <mutex>
#include <atomic>
#include <imgui.h>
#include "Utils.h"
#include "../ReadyornotSDK/SDK.hpp"

// Forward declarations
class ReadyornotOverlay;

// Item types
enum class ItemCacheType {
    PlayerCorpse,
    Evidence,
    Unknown
};

// Actor categories
enum class EActorCategory {
    // Characters
    Player,
    SERT_Red,
    SERT_Blue,
    Suspect,
    Civilian,
    Squad,
    Wounded,
    // Interactive Objects
    Evidence,
    CollectedEvidence,
    Items,
    Doors,
    DoorTraps,
    Securables,
    // World Objects
    CoverLandmarks,
    WallHoles,
    PairedInteractions,
    ReportableActors,
    
    Unknown
};

// Item mapping structure
struct ItemMapping {
    SDK::FString ItemName;
    SDK::FString DisplayName;
    ImU32 Color;
    ItemCacheType Type;
};

// Cached actor info structure
struct CachedActorInfo {
    SDK::AActor* Actor = nullptr;
    EActorCategory Category = EActorCategory::Unknown;
    SDK::FVector WorldPosition;
    SDK::FString DisplayName;
    
    // Item specific info
    ItemCacheType ItemType = ItemCacheType::Unknown;
    ImU32 Color = IM_COL32(255, 255, 255, 255);
    
    // Character info
    std::string CharacterName;
    float Health = 0.0f;
    float MaxHealth = 0.0f;
};

class ActorCache {
public:
    static ActorCache& GetInstance();

    void Initialize(ReadyornotOverlay* overlay);
    void Update();
    void CacheActors();
    void ForceCacheUpdate();
    void ClearCacheDuringLevelTransition();

    // Access cached actors
    std::vector<CachedActorInfo> GetCachedActors() {
        std::lock_guard<std::mutex> lock(CacheMutex);
        return CachedActors;
    }
    
    std::vector<CachedActorInfo> GetCachedPlayers() {
        std::lock_guard<std::mutex> lock(CacheMutex);
        std::vector<CachedActorInfo> result;
        for (const auto& actor : CachedActors) {
            if (actor.Category == EActorCategory::Player) {
                result.push_back(actor);
            }
        }
        return result;
    }
    
    std::vector<CachedActorInfo> GetCachedSERT() {
        std::lock_guard<std::mutex> lock(CacheMutex);
        std::vector<CachedActorInfo> result;
        for (const auto& actor : CachedActors) {
            if (actor.Category == EActorCategory::SERT_Red || actor.Category == EActorCategory::SERT_Blue) {
                result.push_back(actor);
            }
        }
        return result;
    }
    
    std::vector<CachedActorInfo> GetCachedSuspects() {
        std::lock_guard<std::mutex> lock(CacheMutex);
        std::vector<CachedActorInfo> result;
        for (const auto& actor : CachedActors) {
            if (actor.Category == EActorCategory::Suspect) {
                result.push_back(actor);
            }
        }
        return result;
    }
    
    std::vector<CachedActorInfo> GetCachedCivilians() {
        std::lock_guard<std::mutex> lock(CacheMutex);
        std::vector<CachedActorInfo> result;
        for (const auto& actor : CachedActors) {
            if (actor.Category == EActorCategory::Civilian) {
                result.push_back(actor);
            }
        }
        return result;
    }
    
    std::vector<CachedActorInfo> GetCachedWounded() {
        std::lock_guard<std::mutex> lock(CacheMutex);
        std::vector<CachedActorInfo> result;
        for (const auto& actor : CachedActors) {
            if (actor.Category == EActorCategory::Wounded) {
                result.push_back(actor);
            }
        }
        return result;
    }
    
    std::vector<CachedActorInfo> GetCachedEvidence() {
        std::lock_guard<std::mutex> lock(CacheMutex);
        std::vector<CachedActorInfo> result;
        for (const auto& actor : CachedActors) {
            if (actor.Category == EActorCategory::Evidence || 
                actor.Category == EActorCategory::CollectedEvidence) {
                result.push_back(actor);
            }
        }
        return result;
    }
    
    std::vector<CachedActorInfo> GetCachedItems() {
        std::lock_guard<std::mutex> lock(CacheMutex);
        std::vector<CachedActorInfo> result;
        for (const auto& actor : CachedActors) {
            if (actor.Category == EActorCategory::Items) {
                result.push_back(actor);
            }
        }
        return result;
    }
    
    std::vector<CachedActorInfo> GetCachedInteractables() {
        std::lock_guard<std::mutex> lock(CacheMutex);
        std::vector<CachedActorInfo> result;
        for (const auto& actor : CachedActors) {
            if (actor.Category == EActorCategory::Doors || 
                actor.Category == EActorCategory::DoorTraps ||
                actor.Category == EActorCategory::Securables ||
                actor.Category == EActorCategory::PairedInteractions) {
                result.push_back(actor);
            }
        }
        return result;
    }

private:
    ActorCache();
    ~ActorCache() = default;
    
    // Helper methods for processing specific actor types
    CachedActorInfo ProcessCharacter(SDK::AReadyOrNotCharacter* Character, SDK::APlayerController* PlayerController, SDK::AActor* LocalPlayer);
    CachedActorInfo ProcessCharacterByType(SDK::AReadyOrNotCharacter* Character, SDK::APlayerController* PlayerController, SDK::AActor* LocalPlayer);
    CachedActorInfo ProcessEvidence(SDK::AEvidenceActor* Evidence, SDK::APlayerController* PlayerController, SDK::AActor* LocalPlayer);
    CachedActorInfo ProcessCollectedEvidence(SDK::ACollectedEvidenceActor* CollectedEvidence, SDK::APlayerController* PlayerController, SDK::AActor* LocalPlayer);
    CachedActorInfo ProcessItem(SDK::ABaseItem* Item, SDK::APlayerController* PlayerController, SDK::AActor* LocalPlayer);
    CachedActorInfo ProcessDoor(SDK::ADoor* Door, SDK::APlayerController* PlayerController, SDK::AActor* LocalPlayer);
    CachedActorInfo ProcessGenericActor(SDK::AActor* Actor, EActorCategory Category, const std::string& DisplayName, SDK::APlayerController* PlayerController, SDK::AActor* LocalPlayer);

    // Cache variables
    ReadyornotOverlay* OverlayInstance = nullptr;
    double LastCachedTime = 0.0;
    std::chrono::steady_clock::time_point LastRetryTime;
    std::mutex CacheMutex;
    std::atomic<bool> bCacheUpdateInProgress{false};
    
    // Cached actors (double buffer for thread safety)
    std::vector<CachedActorInfo> CachedActors;
    std::vector<CachedActorInfo> BackBufferActors;
    
    // Hash maps for detecting changes
    std::unordered_map<const SDK::AActor*, size_t> ActorHashes;
    std::unordered_set<SDK::AActor*> CachedActorSet;

    // Cache settings
    const float CacheIntervalSeconds = 0.5f;
};

// External color definitions
extern ImU32 PlayerESPColorVisible;
extern ImU32 PlayerESPColorNonVisible;
extern ImU32 PlayerESPColorAimed;
extern ImU32 SERTRedESPColor;
extern ImU32 SERTBlueESPColor;
extern ImU32 SuspectESPColor;
extern ImU32 CivilianESPColor;
extern ImU32 SquadESPColor;
extern ImU32 WoundedESPColor;
extern ImU32 EvidenceESPColor;
extern ImU32 CollectedEvidenceESPColor;
extern ImU32 ItemsESPColor;
extern ImU32 DoorsESPColor;
extern ImU32 TrapsESPColor;
extern ImU32 SecurablesESPColor;