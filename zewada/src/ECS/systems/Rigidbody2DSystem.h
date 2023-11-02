#pragma once

#include "../../physics2d/Physics2D.h"
#include "../core/Coordinator.h"
#include "../../utils/Math.h"

namespace Zewada {
    class Rigidbody2DSystem : public System
    {
    public:
        Rigidbody2DSystem();
        void OnUpdate(float dt);
    };
}