#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../ECS/Components.h"
#include "../../scene/SceneManager.h"
#include "../../ECS/Core/Coordinator.h"
#include "../../events/Event.h"

namespace Zewada {
	class CameraSystem : public System
	{
	private:
		Entity m_maincamera = -1;
		float m_ratio = 16.0f /9.0f;

		void AdjustProjection(const Transform& transform, Camera& cam);
		void AdjustViewMatrix(const Transform& transform, Camera& cam);
	public:
		void OnUpdate(float dt);
		void Resize(float width, float height);
		void DestroyEntity(Entity entity);

		//do that stuff
		const Entity GetMaincameraObject();
		inline const std::set<Entity>& GetEntities() {return m_entities;}

		inline bool HasMainCamera() {return m_maincamera!=-1;}
		Camera& GetMaincamera();
		void SetMaincamera(Entity entity);
	};
}

