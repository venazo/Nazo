#include <zpch.h>
#include "GizmoSystem.h"

namespace Nazo {
	GizmoSystem::GizmoSystem(Application* application, const Camera& camera)
	{
		m_gizmos = application->GetAssetPool()->GetSpriteSheet("assets/nazo/textures/gizmos.png");
		const std::array<glm::vec2, 4>& c_uv = m_gizmos->GetSprite(0)->GetUV();		
		std::array<glm::vec2, 4> UV = 
		{
			glm::vec2(c_uv[0].x, c_uv[0].y + 0.5f),
			glm::vec2(c_uv[1].x, c_uv[1].y),
			glm::vec2(c_uv[2].x, c_uv[2].y),
			glm::vec2(c_uv[3].x, c_uv[3].y + 0.5f)
		};
		std::shared_ptr<Sprite> sprite = m_gizmos->GetSprite(0);
		sprite->SetTexCoords(UV);
		m_translateGizmo = std::make_unique<TranslateGizmo>(application, camera, sprite,m_gizmos->GetSprite(1));
		m_scaleGizmo = std::make_unique<ScaleGizmo>(application, camera, sprite, m_gizmos->GetSprite(2));
		m_usingGizmo = 0;
	}
	void GizmoSystem::OnUpdate(float dt)
	{
		if (m_gameObject.lock() == nullptr)
			return;
		if (!m_gameObject.lock()->operator bool())
			return;
		if (m_usingGizmo == 0)
			m_translateGizmo->OnUpdate(dt);
		else if(m_usingGizmo == 1)
			m_scaleGizmo->OnUpdate(dt);
	}
	void GizmoSystem::SetActiveGameObject(std::weak_ptr<GameObject> go)
	{
		m_gameObject = go;
		if (m_usingGizmo == 0)
		{
			m_translateGizmo->SetActive(m_gameObject);
		}
		else if(m_usingGizmo == 1)
		{
			m_scaleGizmo->SetActive(m_gameObject);
		}
	}

	void GizmoSystem::SetActiveGizmo(int i)
	{
		m_usingGizmo = i;
		if(m_usingGizmo == 0)
		{
			m_scaleGizmo->Reset();
			m_translateGizmo->SetActive(m_gameObject);
		}
		else if(m_usingGizmo == 1)
		{
			m_scaleGizmo->SetActive(m_gameObject);
			m_translateGizmo->Reset();
		}
	}
}