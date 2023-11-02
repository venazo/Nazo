#pragma once

#include "GizmoObject.h"
#include "../CameraController.h"

using namespace Zewada;

namespace Nazo {
	class Gizmo
	{
	private:
		const glm::vec4 xAxisColor = glm::vec4(1.0f, 0.3f, 0.3f, 1.0f);
		const glm::vec4 xAxisColorHover = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		const glm::vec4 yAxisColor = glm::vec4(0.3f, 1.0f, 0.3f, 1.0f);
		const glm::vec4 yAxisColorHover = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		const glm::vec4 xyAxisColor = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
		const glm::vec4 xyAxisColorHover = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);

		glm::vec3 m_xyAxisOffset = glm::vec3(0.0f, 0.0f, 100.0f);
		glm::vec3 m_xAxisOffset = glm::vec3(48.0f + 24.0f - 48.0f, 0.0f + 8.0f - 16.0f, 100.0f);
		glm::vec3 m_yAxisOffset = glm::vec3(16.0f + 8.0f - 16.0f, 48.0f + 24.0f - 48.0f, 100.0f);
		
		glm::vec2 m_xyGizmoSize = glm::vec2(48, 48);
		glm::vec2 m_gizmoSize = glm::vec2(32, 96);

		const Camera& m_camera;

		bool CheckXHoverState();
		bool CheckYHoverState();
		bool CheckXYHoverState();
	protected:
		GizmoObject m_xAxisObject;
		GizmoObject m_yAxisObject;
		GizmoObject m_xyAxisObject;

		bool m_xAxisActive = false;
		bool m_yAxisActive = false;
		bool m_xyAxisActive = false;

		std::weak_ptr<GameObject> m_activeGameObject;

		Application* m_application;
	public:
		Gizmo(Application* application, const Camera& camera, std::shared_ptr<Sprite> xzSprite, std::shared_ptr<Sprite> sprite);
		void OnUpdate(float dt);

		void Reset();
		void SetActive(std::weak_ptr<GameObject> go);
	};
}