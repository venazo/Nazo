#pragma once

#include <Zewada.h>
#include "Gizmo.h"

using namespace Zewada;

namespace Nazo {
	class ScaleGizmo : public Gizmo
	{
	private:
	public:
		ScaleGizmo(Application* application, const Camera& camera, std::shared_ptr<Sprite> xySprite, std::shared_ptr<Sprite> sprite);
		void OnUpdate(float dt);
	};
}