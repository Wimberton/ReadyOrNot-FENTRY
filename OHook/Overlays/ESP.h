#pragma once

#include <imgui.h>
#include "ActorCache.h"
#include "../ReadyornotSDK/SDK.hpp"

namespace ReadyornotESP {
    void DrawGuiESP();
    void DrawGuiFOVCircle();
    void DrawObjectESP(const CachedActorInfo& actorInfo, SDK::APlayerController* PlayerController, SDK::AActor* PawnPlayer, 
                       ImDrawList* drawList, ImVec2 canvasSize);
}
