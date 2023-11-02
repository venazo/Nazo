#pragma once

#include <Zewada.h>
#include "TranslateGizmo.h"
#include "ScaleGizmo.h"

using namespace Zewada;

namespace Nazo {
	class GizmoSystem
	{
	private:
		std::shared_ptr<SpriteSheet> m_gizmos;
		unsigned int m_usingGizmo = 0;

		std::weak_ptr<GameObject> m_gameObject;

		std::unique_ptr<TranslateGizmo> m_translateGizmo;
		std::unique_ptr<ScaleGizmo> m_scaleGizmo;
	public:
		GizmoSystem(Application* application, const Camera& camera);
		void OnUpdate(float dt);
		void SetActiveGameObject(std::weak_ptr<GameObject> go);

		void SetActiveGizmo(int i);
	};
}