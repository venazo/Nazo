#pragma once

#include "ComponentManager.h"
#include <set>
#include <memory>

namespace Zewada {

	class Scene;
	class Coordinator;

	class System
	{
	public:
		std::set<Entity> m_entities;
		std::shared_ptr<Scene> m_scene;
		std::shared_ptr<Coordinator> m_coordinator;
		virtual void Init(std::shared_ptr<Scene> scene, std::shared_ptr<Coordinator> coordinator) {m_scene = scene; m_coordinator = coordinator;}
		virtual void OnUpdate(float dt) = 0;
	};

	class SystemManager
	{
	public:
		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			auto system = std::make_shared<T>();
			mSystems.insert({ typeid(T).name(), system });
			return system;
		}

		template<typename T>
		void SetSignature(Signature signature)
		{
			mSignatures.insert({ typeid(T).name(), signature });
		}

		void EntityDestroyed(Entity entity)
		{
			for (auto const& pair : mSystems)
			{
				auto const& system = pair.second;
				system->m_entities.erase(entity);
			}
		}

		void EntitySignatureChanged(Entity entity, Signature entitySignature)
		{
			for (auto const& pair : mSystems)
			{
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemSignature = mSignatures[type];

				if ((entitySignature & systemSignature) == systemSignature)
				{
					system->m_entities.insert(entity);
				}
				else
				{
					system->m_entities.erase(entity);
				}
			}
		}

	private:
		std::unordered_map<const char*, Signature> mSignatures{};
		std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
	};

}