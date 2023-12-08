#pragma once

#include "ComponentArray.h"

namespace Zewada {

	class ComponentManager
	{
	private:
		std::unordered_map<std::string, unsigned int> m_componentTypes;
		std::unordered_map<std::string, std::shared_ptr<IComponentArray>> m_componentArrays;
		unsigned int m_nextComponentType = 0;
	public:
		template<typename T>
		void RegisterComponent()
		{
			m_componentTypes.insert({ (std::string)typeid(T).name(), m_nextComponentType });
			m_componentArrays.insert({ (std::string)typeid(T).name(), std::make_shared<ComponentArray<T>>() });
			m_nextComponentType++;
		}

		template<typename T>
		unsigned int GetComponentType()
		{
			std::string type = (std::string)typeid(T).name();
			if(Utils::Contains(m_componentTypes, type))
				return m_componentTypes[type];
			else 
			{
				Z_ERROR() << (std::string)typeid(T).name() + " has not been registered!";
				return -1;
			}
		}

		template<typename T>
		T& GetComponent(Entity entity)
		{
			return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeid(T).name()])->GetData(entity);
		}

		template<typename T>
		void AddComponent(Entity entity, T component)
		{
			return GetComponentArray<T>()->AddData(entity, component);
		}

		template<typename T>
		void RemoveComponent(Entity entity)
		{
			GetComponentArray<T>()->RemoveData(entity);
		}

		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray()
		{
			std::string type = typeid(T).name();
			if(Utils::Contains(m_componentArrays, type))
				return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[type]);
			else
			{
				Z_ERROR() << type + " has not been registered!";
				return std::make_shared<ComponentArray<T>>();
			}
		}

		void EntityDestroyed(Entity entity)
		{
			for (auto const& pair : m_componentArrays)
			{
				auto const& component = pair.second;

				component->EntityDestroyed(entity);
			}
		}
	};
}