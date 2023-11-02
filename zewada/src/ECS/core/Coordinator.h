#pragma once

#include "ComponentManager.h"
#include "SystemManager.h"
#include "EntityManager.h"

namespace Zewada {

	class Coordinator
	{
	private:
		std::unique_ptr<ComponentManager> m_componentManager;
		std::unique_ptr<EntityManager> m_entityManager;
		std::unique_ptr<SystemManager> m_systemManager;
	public:
		Coordinator()
		{
			m_componentManager = std::make_unique<ComponentManager>();
			m_entityManager = std::make_unique<EntityManager>();
			m_systemManager = std::make_unique<SystemManager>();
		}

		~Coordinator()
		{
			
		}

		template<typename T>
		void RegisterComponent()
		{
			m_componentManager->RegisterComponent<T>();
		}

		Entity CreateEntity()
		{
			return m_entityManager->CreateEntity();
		}

		template<typename T>
		bool HasComponent(Entity entity)
		{
			auto signature = m_entityManager->GetSignature(entity);
			return signature[m_componentManager->GetComponentType<T>()];
		}

		template<typename T>
		void AddComponent(T component, Entity entity)
		{
			m_componentManager->AddComponent(entity, component);

			auto signature = m_entityManager->GetSignature(entity);
			signature.set(m_componentManager->GetComponentType<T>(), true);
			m_entityManager->SetSignature(entity, signature);

			m_systemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		void RemoveComponent(Entity entity)
		{
			m_componentManager->RemoveComponent<T>(entity);

			auto signature = m_entityManager->GetSignature(entity);
			signature.set(m_componentManager->GetComponentType<T>(), false);
			m_entityManager->SetSignature(entity, signature);

			m_systemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		T& GetComponent(Entity entity)
		{
			if(HasComponent<T>(entity))
			{
				return m_componentManager->GetComponent<T>(entity);
			}
			else
			{
				Z_WARN("Entity " + std::to_string(entity) + " had no " + typeid(T).name() + " Component!");
				AddComponent<T>(T(), entity);
				return m_componentManager->GetComponent<T>(entity);
			}
		}

		template<typename T>
		unsigned int GetComponentType()
		{
			return m_componentManager->GetComponentType<T>();
		}

		void DestroyEntity(Entity entity)
		{
			m_componentManager->EntityDestroyed(entity);
			m_systemManager->EntityDestroyed(entity);
			m_entityManager->DestroyEntity(entity);
		}

		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			return m_systemManager->RegisterSystem<T>();
		}

		template<typename T>
		void SetSystemSignature(Signature& signature)
		{
			m_systemManager->SetSignature<T>(signature);
		}

		inline const std::vector<Entity>& GetAllEntities() { return m_entityManager->GetUsedEntities(); }
	};
}