#pragma once

#include <glm/glm.hpp>
#include "../utils/debug/Logger.h"

namespace Zewada {

    class GameObject;

    class Physics2D
    {
    private:
    public:
        Physics2D();

        void OnStart();
        void OnUpdate(float dt);
        void OnStop();
    };
}   