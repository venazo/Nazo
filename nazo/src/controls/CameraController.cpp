#include <zpch.h>
#include "CameraController.h"
#include "../NazoApplication.h"

namespace Nazo {
#define BIND_EVENT_FN(x) std::bind(&Nazo::CameraController::x, this, std::placeholders::_1)
	CameraController::CameraController(NazoApplication* application)
	{
		m_camera = Camera();
		m_transform = Transform();
		m_application = application;
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OnMouseScroll));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
	}

	void CameraController::OnUpdate(float dt)
	{
		AdjustProjection();
		AdjustViewMatrix();
		Drag(dt);
	}

	bool CameraController::OnResize(float width, float height)
	{
		m_transform.scale.x = width;
		m_transform.scale.y = height;
		return false;
	}

	bool CameraController::OnKeyPressed(KeyPressedEvent& event)
	{
		if(event.GetKeyCode() == GLFW_KEY_Q)
		{
			m_camera.zoom = 1.0f;
			m_transform.worldPos = glm::vec3();
			return true;
		}
		return false;
	}

	void CameraController::AdjustProjection()
	{
		m_camera.projectionMatrix = glm::ortho(-m_transform.scale.x /2 * m_camera.zoom, m_transform.scale.x / 2 * m_camera.zoom, -m_transform.scale.y / 2 * m_camera.zoom, m_transform.scale.y /2 * m_camera.zoom, 0.0f, 100.0f);
	}

	void CameraController::AdjustViewMatrix()
	{
		glm::vec3 cameraFront(m_transform.worldPos.x, m_transform.worldPos.y, m_transform.worldPos.z);
		glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
		m_camera.viewMatrix = glm::lookAt(glm::vec3(m_transform.worldPos.x, m_transform.worldPos.y, m_transform.worldPos.z + 100.0f), m_transform.worldPos, cameraUp);
	}


	bool CameraController::OnMouseScroll(MouseScrolledEvent& event)
	{
		Zoom(event.GetYOffset());
		return false;
	}

	void CameraController::Drag(float dt)
	{
		if (m_application->GetInput()->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE) && m_dragDebounce > 0)
		{
			if (m_application->GetImGuiLayer()->GetEditorView()->IsHovering())
			{
				m_clickedPos = m_application->GetInput()->GetMousePosition();
				m_clickedPos.y = -(m_clickedPos.y - m_application->GetWindow()->GetHeight());
				m_dragDebounce -= dt;
			}

			return;
		}
		else if (m_application->GetInput()->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE))
		{
			glm::vec2 mousePos = m_application->GetInput()->GetMousePosition();
			mousePos.y = -(mousePos.y - m_application->GetWindow()->GetHeight());
			glm::vec2 delta = mousePos - m_clickedPos;
			m_transform.worldPos.x -= delta.x * m_dragSens * m_camera.zoom;
			m_transform.worldPos.y -= delta.y * m_dragSens * m_camera.zoom;
			m_clickedPos = mousePos;
		}

		if (m_dragDebounce <= 0.0f && !m_application->GetInput()->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE))
		{
			m_dragDebounce = 0.032f;
		}
	}

	void CameraController::Zoom(float scrollY)
	{
		float addValue = pow(abs(scrollY * pow(m_camera.zoom * m_scrollSens, m_camera.zoom)), 1 / m_camera.zoom);
		addValue *= -sgn(scrollY);
		m_camera.zoom += addValue;
	}
}