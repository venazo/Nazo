#pragma once

#include "../Scene/SceneManager.h"
#include "../ECS/Components.h"
#include "../ECS/core/Coordinator.h"
#include "Scene.h"

namespace Zewada {

	class GameObject
	{
	private:
		Entity m_entity{-1};
		std::weak_ptr<Scene> m_scene;
		std::weak_ptr<Coordinator> m_coordinator;
	public:
		GameObject() = default;
		GameObject(Entity entity, std::shared_ptr<Scene> scene);
		~GameObject();

		void Destroy();
		void SetWorldPos(const glm::vec3& pos);
		void AddWorldScale(float x, float y);

		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& vec);

		void Set2DVelocity(const glm::vec2& vec);
		void Set2DVelocity(float x, float y);

		void Add2DVelocity(const glm::vec2& vec);
		void Add2DVelocity(float x, float y);

		template<typename T>	
		void AddComponent(T component)
		{
			m_coordinator.lock()->AddComponent<T>(component, m_entity);
		}

		template<typename T>
		void AddComponent()
		{
			m_coordinator.lock()->AddComponent<T>(T(), m_entity);
		}

		template<typename T>
		bool HasComponent() const
		{
			return m_coordinator.lock()->HasComponent<T>(m_entity);
		}

		template<typename T>
		T& GetComponent() const
		{
			return m_coordinator.lock()->GetComponent<T>(m_entity);
		}

		template<typename T>
		void RemoveComponent()
		{
			m_coordinator.lock()->RemoveComponent<T>(m_entity);
		}

		void SetPosition(float x, float y);

		GameObject Copy() const;

		inline std::weak_ptr<Scene> GetScene() const {return m_scene;}

		inline const Entity& GetID() const { return m_entity; }

		operator bool() const { return m_entity != -1; }
	};
}
