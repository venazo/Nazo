#pragma once

#include <ECS/Components.h>
#include <Utils/Input.h>
#include <math.h>
#include "Utils/Math.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Zewada.h>

using namespace Zewada;

namespace Nazo {

	class NazoApplication;

	class CameraController
	{
	private:
		float m_dragDebounce = 0.032f;
		glm::vec2 m_clickedPos;
		float m_dragSens = 1.0f;
		float m_scrollSens = 0.1f;

		Camera m_camera;
		Transform m_transform;

		NazoApplication* m_application;

		void Drag(float dt);
		void Zoom(float scrollY);
		bool OnMouseScroll(Zewada::MouseScrolledEvent& event);
		bool OnKeyPressed(KeyPressedEvent& event);

		void AdjustViewMatrix();
		void AdjustProjection();
	public:
		CameraController(NazoApplication* application);
		void OnUpdate(float dt);
		void OnEvent(Zewada::Event& e);
		bool OnResize(float width, float height);

		inline const Transform& GetTransform() {return m_transform;}
		inline Camera& GetCamera(){return m_camera;}
	};
}