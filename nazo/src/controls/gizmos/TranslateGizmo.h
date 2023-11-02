#pragma once

#include <Zewada.h>
#include "Gizmo.h"

using namespace Zewada;

namespace Nazo {
	class TranslateGizmo : public Gizmo
	{
	private:
	public:
		TranslateGizmo(Application* application, const Camera& camera, std::shared_ptr<Sprite> xySprite, std::shared_ptr<Sprite> sprite);
		void OnUpdate(float dt);
	};
}