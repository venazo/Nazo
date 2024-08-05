#pragma once

#include "../core/Coordinator.h"
#include "../../scene/SceneManager.h"

namespace Zewada
{
    class TransformSystem : public System {
    public:
        TransformSystem();
        void OnUpdate(float dt);
        void OnStart();

        void CalcPos(Entity entity);
        void CalcSize(Entity entity);
    };
}