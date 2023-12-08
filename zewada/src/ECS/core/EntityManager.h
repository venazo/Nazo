#pragma once

#include "SystemManager.h"
#include <queue>
#include <algorithm>

namespace Zewada {

	class EntityManager
	{
	private:
		std::queue<Entity> m_availableEntities;
		std::vector<Entity> m_usedEntities{};
		std::unordered_map<unsigned int, Signature> m_signatures;
		unsigned int m_entities{};
	public:
		EntityManager()
		{
			m_entities++;
			for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
			{
				m_availableEntities.push(entity);
			}
		}

		Entity CreateEntity()
		{
			if (m_entities >= MAX_ENTITIES)
			{
				Z_WARN() << "MAX Entities";
			}
			Entity id = m_availableEntities.front();
			m_availableEntities.pop();
			m_usedEntities.push_back(id);
			m_entities++;

			return id;
		}

		Signature& GetSignature(Entity entity)
		{
			return m_signatures[entity];
		}

		void SetSignature(Entity entity, Signature signature)
		{
			m_signatures[entity] = signature;
		}

		void DestroyEntity(Entity entity)
		{
			m_availableEntities.push(entity);
			m_usedEntities.erase(std::remove(m_usedEntities.begin(), m_usedEntities.end(), entity), 
				m_usedEntities.end());
			m_signatures.erase(entity);
			m_entities--;
		}

		inline const std::vector<Entity>& GetUsedEntities() const { return m_usedEntities; }
	};
}
