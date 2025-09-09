#pragma once
#include "SDKExt.h"
#include "ReadyornotOverlay.h"
#include "Configuration.h"
#include <SDK.hpp>

using namespace SDK;

class ReadyornotOverlay;

namespace AimFeatures {
    void DoTargeting(ReadyornotOverlay* Overlay, const SDK::AHUD* HUD);
    void DoAimbot(ReadyornotOverlay* Overlay, const SDK::AHUD* HUD);
    void DoInfiniteAmmo();
    void RemoveWeaponEffects();
}
