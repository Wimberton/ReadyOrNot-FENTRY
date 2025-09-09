#ifndef DETOUR_MANAGER_H
#define DETOUR_MANAGER_H

#pragma once

#include <unordered_set>
#include "../ReadyornotSDK/SDK.hpp"
#include <Imgui.h>

class ReadyornotOverlay;

using namespace SDK;

inline static void (__fastcall *OriginalProcessEvent)(const UObject*, const UFunction*, void*);
inline static std::unordered_set<std::string> invocations;
inline static void* HookedClient;
inline static UFont* Roboto;

inline static ULevel* CurrentLevel = nullptr;
inline static AGameStateBase* CachedGameState = nullptr;

extern ImU32 PlayerESPColorVisible;
extern ImU32 PlayerESPColorAimed;
extern ImU32 PlayerESPColorNonVisible;

extern ImU32 LootableColorWeapon;
extern ImU32 LootableColorCorpse;
extern ImU32 LootableColorChest;
extern ImU32 LootableColorResources;
extern ImU32 LootableColorConsumableNatural;
extern ImU32 LootableColorConsumableProcessed;
extern ImU32 LootableColorSpecial;
extern ImU32 LootableColorAirDrop;
extern ImU32 LootableColorSafes;
extern ImU32 LootableColorContainer;
extern ImU32 LootableColorDefault;

class DetourManager final {

public:
    DetourManager() = default;

    static inline void ProcessEventDetourCallback(const UObject* Class, const UFunction* Function, void* Params, const DetourManager* manager);
    static inline void ProcessEventDetour(const UObject* Class, const UFunction* Function, void* Params);
    static void SetupDetour(void* Instance, void (*DetourFunc)(const UObject*, const UFunction*, void*));
    static void SetupDetour(void* Instance);
};

#endif