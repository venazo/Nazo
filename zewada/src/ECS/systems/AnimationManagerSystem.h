#pragma once
#include "../core/Coordinator.h"

namespace Zewada
{
    class AnimationManagerSystem : public System
    {
    public:
        void Init(std::shared_ptr<Scene> scene, std::shared_ptr<Coordinator> coordinator) override;
        void OnStart();
        void OnUpdate(float dt) override;
    };
}