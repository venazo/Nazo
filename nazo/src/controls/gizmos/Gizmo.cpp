#include <zpch.h>
#include "Gizmo.h"

namespace Nazo {
	Gizmo::Gizmo(Application* application, const Camera& camera, std::shared_ptr<Sprite> xySprite, std::shared_ptr<Sprite> sprite)
		:m_camera(camera)
	{
		m_application = application;
		m_xAxisObject.ID = MAX_ENTITIES + 1;
		m_yAxisObject.ID = MAX_ENTITIES + 2;
		m_xyAxisObject.ID = MAX_ENTITIES + 3;
		m_xAxisObject.transform.worldScale = m_gizmoSize;
		m_yAxisObject.transform.worldScale = m_gizmoSize;
		m_xyAxisObject.transform.worldScale = m_xyGizmoSize;
		m_xAxisObject.transform.rotation = 90.0f;
		m_yAxisObject.transform.rotation = 180.0f;
		m_xAxisObject.spriteRenderer = SpriteRenderer(sprite);
		m_yAxisObject.spriteRenderer = SpriteRenderer(sprite);
		m_xyAxisObject.spriteRenderer = SpriteRenderer(xySprite);
		m_activeGameObject.reset();
	}

	void Gizmo::OnUpdate(float dt)
	{
		if (m_activeGameObject.lock() != nullptr)
		{
			//calculate Size
			float zoom = m_camera.zoom;
			m_xAxisObject.transform.worldScale = m_gizmoSize * zoom;
			m_yAxisObject.transform.worldScale = m_gizmoSize * zoom;
			m_xyAxisObject.transform.worldScale = m_xyGizmoSize * zoom;
			m_xAxisOffset = glm::vec3(m_xyAxisObject.transform.worldScale.y + (0.5f * m_yAxisObject.transform.worldScale.y), 0.0f, 0.0f);
			m_yAxisOffset = glm::vec3(0.0f, m_xyAxisObject.transform.worldScale.x + (0.5f * m_yAxisObject.transform.worldScale.y), 0.0f);
			m_xyAxisOffset = glm::vec3(0.0, 0.0f, 0.0f);

			Transform& transform = m_activeGameObject.lock()->GetComponent<Transform>();
			m_xAxisObject.transform.worldPos = transform.worldPos;
			m_yAxisObject.transform.worldPos = transform.worldPos;
			m_xyAxisObject.transform.worldPos = transform.worldPos;
			m_xAxisObject.transform.worldPos += m_xAxisOffset;
			m_yAxisObject.transform.worldPos += m_yAxisOffset;
			m_xyAxisObject.transform.worldPos += m_xyAxisOffset;
			m_xAxisObject.transform.worldPos.z = 100.0f;
			m_yAxisObject.transform.worldPos.z = 100.0f;
			m_xyAxisObject.transform.worldPos.z = 100.0f;
		}

		bool xAxisHot = CheckXHoverState();
		bool yAxisHot = CheckYHoverState();
		bool xyAxisHot = CheckXYHoverState();

		if ((xAxisHot || m_xAxisActive) && !m_xyAxisActive && !m_yAxisActive && m_application->GetInput()->IsDraging() && m_application->GetInput()->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			m_xAxisActive = true;
			m_yAxisActive = false;
			m_xyAxisActive = false;
		}
		else if ((yAxisHot || m_yAxisActive) && !m_xyAxisActive && !m_xAxisActive && m_application->GetInput()->IsDraging() && m_application->GetInput()->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			m_yAxisActive = true;
			m_xAxisActive = false;
			m_xyAxisActive = false;
		}
		else if ((m_xyAxisActive || xyAxisHot) && !m_xAxisActive && !m_yAxisActive && m_application->GetInput()->IsDraging() && m_application->GetInput()->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			m_yAxisActive = false;
			m_xAxisActive = false;
			m_xyAxisActive = true;
		}
		else
		{
			m_xAxisActive = false;
			m_yAxisActive = false;
			m_xyAxisActive = false;
		}
		
		if (m_activeGameObject.lock() != nullptr)
		{
			m_application->GetRenderer2D()->Submit(&m_xAxisObject.transform, &m_xAxisObject.spriteRenderer, m_xAxisObject.ID);
			m_application->GetRenderer2D()->Submit(&m_yAxisObject.transform, &m_yAxisObject.spriteRenderer, m_yAxisObject.ID);
			m_application->GetRenderer2D()->Submit(&m_xyAxisObject.transform, &m_xyAxisObject.spriteRenderer, m_xyAxisObject.ID);
		}
	}

	void Gizmo::SetActive(std::weak_ptr<GameObject> go)
	{
		m_activeGameObject = go;
	}

	bool Gizmo::CheckXHoverState()
	{
		glm::vec2 mousePos = m_application->GetInput()->GetWorldMousePosition();
		if (mousePos.x <= m_xAxisObject.transform.worldPos.x + (m_xAxisObject.transform.worldScale.y * 0.5f)&&
			mousePos.x >= m_xAxisObject.transform.worldPos.x + (m_xAxisObject.transform.worldScale.y * -0.5f) &&
			mousePos.y >= m_xAxisObject.transform.worldPos.y + (m_xAxisObject.transform.worldScale.x * -0.5f)&&
			mousePos.y <= m_xAxisObject.transform.worldPos.y + (m_xAxisObject.transform.worldScale.x * 0.5f))
		{
			m_xAxisObject.spriteRenderer.color = xAxisColorHover;
			return true;
		}

		m_xAxisObject.spriteRenderer.color = xAxisColor;
		return false;
	}

	bool Gizmo::CheckYHoverState()
	{
		glm::vec2 mousePos = m_application->GetInput()->GetWorldMousePosition();
		if (mousePos.x <= m_yAxisObject.transform.worldPos.x + (m_yAxisObject.transform.worldScale.x * 0.5f)&&
			mousePos.x >= m_yAxisObject.transform.worldPos.x + (m_yAxisObject.transform.worldScale.x * -0.5f) &&
			mousePos.y <= m_yAxisObject.transform.worldPos.y + (m_yAxisObject.transform.worldScale.y * 0.5f)&&
			mousePos.y >= m_yAxisObject.transform.worldPos.y + (m_yAxisObject.transform.worldScale.y * -0.5f))
		{
			m_yAxisObject.spriteRenderer.color = yAxisColorHover;
			return true;
		}

		m_yAxisObject.spriteRenderer.color = yAxisColor;
		return false;
	}
	bool Gizmo::CheckXYHoverState()
	{
		glm::vec2 mousePos = m_application->GetInput()->GetWorldMousePosition();
		if (mousePos.x >= m_xyAxisObject.transform.worldPos.x + (m_xyAxisObject.transform.worldScale.x * -0.5f)&&
			mousePos.x <= m_xyAxisObject.transform.worldPos.x + (m_xyAxisObject.transform.worldScale.x * 0.5f) &&
			mousePos.y >= m_xyAxisObject.transform.worldPos.y + (m_xyAxisObject.transform.worldScale.y * -0.5f) &&
			mousePos.y <= m_xyAxisObject.transform.worldPos.y + (m_xyAxisObject.transform.worldScale.y * 0.5f))
		{
			m_xyAxisObject.spriteRenderer.color = xyAxisColorHover;
			return true;
		}

		m_xyAxisObject.spriteRenderer.color = xyAxisColor;
		return false;
	}

	void Gizmo::Reset()
	{
		m_activeGameObject.reset();
	}
}