#pragma once

#include "../../Scene/SceneManager.h"
#include "../../Graphics/OpenGL/Renderer/Renderer2D.h"
#include "../Components.h"


namespace Zewada {
	class SpriteRendererSystem : public System
	{
	public:
		void OnUpdate(float dt) override;
	};
}