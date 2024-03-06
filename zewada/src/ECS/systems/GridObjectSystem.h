#pragma once
#include "../core/Coordinator.h"

namespace Zewada {
    class GridObjectSystem : public System
    {
    public:
        void OnStart();
        void OnUpdate(float dt) override;
    };
}

