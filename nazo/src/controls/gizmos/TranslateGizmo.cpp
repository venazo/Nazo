#include <zpch.h>
#include "TranslateGizmo.h"

namespace Nazo {
	TranslateGizmo::TranslateGizmo(Application* application, const Camera& camera, std::shared_ptr<Sprite> xySprite, const std::shared_ptr<Sprite> sprite)
		:Gizmo(application, camera, xySprite, sprite)
	{
	
	}

	void TranslateGizmo::OnUpdate(float dt)
	{
		Gizmo::OnUpdate(dt);
		if (m_activeGameObject.lock() != nullptr)
		{
			if (m_xAxisActive)
				m_activeGameObject.lock()->GetComponent<Transform>().pos.x -= m_application->GetInput()->GetDWorldMousePosition().x;
			else if (m_yAxisActive)
				m_activeGameObject.lock()->GetComponent<Transform>().pos.y -= m_application->GetInput()->GetDWorldMousePosition().y;
			else if (m_xyAxisActive)
			{
				glm::vec3 pos = glm::vec3(m_application->GetInput()->GetDWorldMousePosition(), 0.0f);
				m_activeGameObject.lock()->GetComponent<Transform>().pos -= pos;
			}
		}
	}
}