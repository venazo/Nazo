#pragma once

#include "../../graphics/openGL/renderables/Font.h"
#include "../core/Coordinator.h"
#include "../../graphics/openGL/renderer/Shader.h"
#include "../Components.h"

namespace Zewada
{
    class TextSystem : public System
    {
    private:
        std::vector<Transform*> m_transforms;
        std::vector<SpriteRenderer*> m_spriteRenderers;
	public:
		void OnUpdate(float dt) override;
    };
}