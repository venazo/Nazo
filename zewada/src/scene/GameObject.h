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
		std::shared_ptr<Scene> m_scene;
		std::shared_ptr<Coordinator> m_coordinator;
	public:
		GameObject() = default;
		GameObject(Entity entity, std::shared_ptr<Scene> scene);
		~GameObject();

		void Destroy();

		void AddWorldScale(float x, float y);

		void SetWorldPos(float x, float y, float z = 0.0f);
		void SetWorldPos(const glm::vec3& pos);

		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& vec);

		void AddRotation(float r);
		void SetRotation(float r);


		template<typename T>	
		void AddComponent(T component)
		{
			m_coordinator->AddComponent<T>(component, m_entity);
		}

		template<typename T>
		void AddComponent()
		{
			m_coordinator->AddComponent<T>(T(), m_entity);
		}

		template<typename T>
		bool HasComponent() const
		{
			return m_coordinator->HasComponent<T>(m_entity);
		}

		template<typename T>
		T& GetComponent() const
		{
			return m_coordinator->GetComponent<T>(m_entity);
		}

		template<typename T>
		void RemoveComponent()
		{
			m_coordinator->RemoveComponent<T>(m_entity);
		}

		void SetPosition(float x, float y);

		GameObject Copy() const;

		inline std::shared_ptr<Scene> GetScene() const {return m_scene;}

		inline const Entity& GetID() const { return m_entity; }

		operator bool() const { return m_entity != -1; }

		static GameObject* GetNullObject(); 
	};
}
