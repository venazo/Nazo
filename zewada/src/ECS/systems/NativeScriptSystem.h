#pragma once

#include "../core/Coordinator.h"
#include "../../utils/resource/ScriptLoader.h"

namespace Zewada
{
    class NativeScriptSystem : public System
    {
    public:
        void OnStart();
        void OnUpdate(float dt) override;
    };
}