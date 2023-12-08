#pragma once

#include "../../Utils/Debug/Logger.h"
#include "../../utils/Utils.h"

#define MAX_COMPONENTS 10
#define MAX_ENTITIES 10000

using Signature = std::bitset<MAX_COMPONENTS>;
using Entity = int;

namespace Zewada {

	class IComponentArray
	{
	public:
		virtual void EntityDestroyed(Entity entity) = 0;
	};

	template<typename T>
	class ComponentArray : public IComponentArray
	{
	private:
		std::array<T, MAX_ENTITIES> m_components {};
		std::unordered_map<Entity, unsigned int> m_entity2Index {};
		std::unordered_map<unsigned int, Entity> m_index2Entity{};
		unsigned int m_size;
	public:
		void AddData(Entity entity, T component)
		{
			std::string componentName = typeid(T).name();
			if (m_size >= MAX_ENTITIES)
			{
				Z_ERROR() << componentName + " has no space for GameObject " + std::to_string(entity) + " left!";
				return;
			}
			m_entity2Index[entity] = m_size;
			m_index2Entity[m_size] = entity;
			m_components[m_entity2Index[entity]] = component;
			m_size++;
		}

		T& GetData(Entity entity)
		{
			return m_components[m_entity2Index[entity]];
		}

		void RemoveData(Entity entity)
		{
			unsigned int indexOfRemovedEntity = m_entity2Index[entity];
			m_components[indexOfRemovedEntity] = m_components[m_size - 1];

			unsigned int IDOfLastElement = m_index2Entity[m_size - 1];
			m_entity2Index[IDOfLastElement] = indexOfRemovedEntity;
			m_index2Entity[indexOfRemovedEntity] = IDOfLastElement;

			m_entity2Index.erase(entity);
			m_index2Entity.erase(m_size - 1);

			m_size--;
		}

		void EntityDestroyed(Entity entity) override
		{
			if (Utils::Contains(m_entity2Index, entity))
			{
				RemoveData(entity);
			}
		}
	};
}