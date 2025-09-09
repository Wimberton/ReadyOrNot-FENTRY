#pragma once
#include "SDKExt.h"
#include "ReadyornotOverlay.h"
#include "Configuration.h"
#include <SDK.hpp>

using namespace SDK;

// Forward declarations
class ReadyornotOverlay;

namespace PlayerFeatures {
    void DoNoClip();
    void DoSpeedmod();
    void DoCustomFOV();
    void DoGodmode();
    void DisableGodmode();
    void DoNoSuspectFirefight();
    void DoDisarmAllSuspects();
    void DoForceSuspectSurrender();
    void DoAutoComplySuspects();
    void DoDisableAllTraps();
}
