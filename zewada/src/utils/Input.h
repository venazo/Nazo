#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../events/MouseEvent.h"
#include "../events/KeyEvent.h"
#include "../events/ApplicationEvent.h"
#include "../ECS/Components.h"

namespace Zewada {

	class Application;

	class Input 
	{
	private:
		bool m_translated;
		glm::vec4 m_translation;

		glm::vec2 m_mousePosition, m_lastMousePosition;
		glm::vec2 m_absoluteMousePosition, m_lastAbsoluteMousePosition;
		glm::vec2 m_worldMousePosition, m_dWorldMousePosition;

		bool m_isDraging;
		int m_mouseButtondown;

		Application* m_application;
	public:
		Input(Application* application);

		void OnEvent(Event& event);

		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);

		bool IsKeyPressed(unsigned int keycode);
		bool IsMouseButtonPressed(unsigned int keycode);

		//first 2 float pos other 2 size
		void SetTranslation(const glm::vec4& translation);
		void SetTranslationState(bool value);

		inline const glm::vec2& GetAbsoluteMousePosition() { return m_absoluteMousePosition; }
		inline const glm::vec2& GetMousePosition() { return m_mousePosition; };
		inline const glm::vec2& GetWorldMousePosition() { return m_worldMousePosition; };

		inline const glm::vec2& GetDWorldMousePosition(){return m_dWorldMousePosition;};

		void CalcAbsoluteMousePosition();
		void CalcMousePosition();
		void CalcWorldMousePosition(const Transform& transform, const Camera& camera);

		bool IsDraging() { return m_isDraging; }
	};
}
