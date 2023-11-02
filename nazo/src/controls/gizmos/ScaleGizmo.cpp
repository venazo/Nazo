#include <zpch.h>
#include "ScaleGizmo.h"

namespace Nazo {
	ScaleGizmo::ScaleGizmo(Application* application, const Camera& camera, std::shared_ptr<Sprite> xySprite, std::shared_ptr<Sprite> sprite)
		:Gizmo(application, camera, xySprite, sprite)
	{

	}

	void ScaleGizmo::OnUpdate(float dt)
	{
		Gizmo::OnUpdate(dt);
		if (m_activeGameObject.lock() != nullptr)
		{
			if (m_xAxisActive)
				m_activeGameObject.lock()->AddWorldScale(-m_application->GetInput()->GetDWorldMousePosition().x, 0.0f);
			else if (m_yAxisActive)
				m_activeGameObject.lock()->AddWorldScale(0.0f, -m_application->GetInput()->GetDWorldMousePosition().y);
			else if (m_xyAxisActive)
			{
				m_activeGameObject.lock()->AddWorldScale(-m_application->GetInput()->GetDWorldMousePosition().x, -m_application->GetInput()->GetDWorldMousePosition().y);
			}
		}
	}
}