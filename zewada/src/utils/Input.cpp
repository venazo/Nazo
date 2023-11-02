#include <zpch.h>
#include "Input.h"
#include "../Application.h"

namespace Zewada {

#define BIND_EVENT_FN(x) std::bind(&Zewada::Input::x, this, std::placeholders::_1)

	Input::Input(Application* application)
	{
		m_application = application;
		m_mouseButtondown = 0;
		m_isDraging = false;
		m_translated = false;
	}

	bool Input::IsKeyPressed(unsigned int keycode)
	{
		auto* window = static_cast<GLFWwindow*>(m_application->GetWindow()->GetGLFWwindow());
		auto state = glfwGetKey(window, keycode);
		if(state == GLFW_PRESS)
			return true;
		
		return false;
	}

	bool Input::IsMouseButtonPressed(unsigned int keycode)
	{
		auto* window = static_cast<GLFWwindow*>(m_application->GetWindow()->GetGLFWwindow());
		auto state = glfwGetMouseButton(window, keycode);
		if(state == GLFW_PRESS)
			return true;
		
		return false;
	}

	void Input::SetTranslation(const glm::vec4& translation)
	{
		m_translation = translation;
	}

	void Input::SetTranslationState(bool value)
	{
		m_translated = value;
	}

	void Input::CalcAbsoluteMousePosition()
	{
		m_lastAbsoluteMousePosition = m_absoluteMousePosition;
		auto* window = static_cast<GLFWwindow*>(m_application->GetWindow()->GetGLFWwindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		m_absoluteMousePosition = glm::vec2((float)xpos, (float)ypos);
	}

	void Input::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(OnMouseButtonPressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(OnMouseButtonReleased));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(OnMouseMoved));
	}

	bool Input::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		m_mouseButtondown++;
		return false;
	}

	bool Input::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		m_mouseButtondown--;
		m_isDraging = false;
		return false;
	}

	bool Input::OnMouseMoved(MouseMovedEvent& e)
	{
		if (m_mouseButtondown > 0)
			m_isDraging = true;
		return false;
	}

	void Input::CalcMousePosition()
	{
		m_lastMousePosition = m_mousePosition;
		glm::vec2 result = GetAbsoluteMousePosition();
		if (m_translated)
		{
			result -= glm::vec2(m_translation);
			result.x = result.x / m_translation.z * m_application->GetWindow()->GetWidth();
			result.y = result.y / m_translation.w * m_application->GetWindow()->GetHeight();
		}

		m_mousePosition = result;
	}

	void Input::CalcWorldMousePosition(const Transform& transform, const Camera& cam)
	{
		glm::vec2 result = GetAbsoluteMousePosition();
		if (!m_translated)
		{
			result.x = result.x / m_application->GetWindow()->GetWidth() * 2.0f - 1.0f;
			result.y = -(result.y / m_application->GetWindow()->GetHeight() * 2.0f - 1.0f);
		}
		else
		{
			result -= glm::vec2(m_translation);
			result.x = result.x / m_translation.z * 2.0f - 1.0f;
			result.y = -(result.y / m_translation.w * 2.0f - 1.0f);
		}

		glm::mat4 viewProjection;
		viewProjection = glm::inverse(cam.projectionMatrix) * glm::inverse(cam.viewMatrix);
		result = viewProjection * glm::vec4(result, 0, 0) + glm::vec4(transform.worldPos, 1.0f);

		m_worldMousePosition = result;

		glm::vec2 lastWorldPos = m_lastAbsoluteMousePosition;
		if(!m_translated)
		{
			lastWorldPos.x = lastWorldPos.x / m_application->GetWindow()->GetWidth() * 2.0f - 1.0f;
			lastWorldPos.y = -(lastWorldPos.y / m_application->GetWindow()->GetHeight() * 2.0f - 1.0f);
		}
		else
		{
			lastWorldPos -= glm::vec2(m_translation);
			lastWorldPos.x = lastWorldPos.x / m_translation.z * 2.0f - 1.0f;
			lastWorldPos.y = -(lastWorldPos.y / m_translation.w * 2.0f - 1.0f);
		}

		lastWorldPos = viewProjection * glm::vec4(lastWorldPos, 0, 0) + glm::vec4(transform.worldPos, 1.0f);

		m_dWorldMousePosition = lastWorldPos - result;
	}
}