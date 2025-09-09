#pragma once

#include <SDK.hpp>
#include <vector>

namespace SDK {
    inline UEngine* GetEngine() {
        static UEngine* GEngine = nullptr;

        if (!GEngine) {
            for (int i = 0; i < UObject::GObjects->Num(); i++) {
                UObject* Obj = UObject::GObjects->GetByIndex(i);

                if (!Obj)
                    continue;

                if (Obj->IsA(UEngine::StaticClass()) && !Obj->IsDefaultObject()) {
                    GEngine = static_cast<UEngine*>(Obj);
                    break;
                }
            }
        }

        return GEngine;
    }

    inline UWorld* GetWorld() {
        if (const UEngine* Engine = GetEngine()) {
            if (!Engine->GameViewport)
                return nullptr;
            return Engine->GameViewport->World;
        }
        return nullptr;
    }
    
}

namespace SDKExt {

}
