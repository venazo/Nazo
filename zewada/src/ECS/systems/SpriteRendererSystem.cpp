#include <zpch.h>
#include "SpriteRendererSystem.h"
#include "../../scene/Scene.h"

namespace Zewada {

	void SpriteRendererSystem::OnUpdate(float dt)
	{
		for (Entity entity : m_entities)
		{
			m_scene.lock()->GetApplication()->GetRenderer2D()->Submit(&m_coordinator.lock()->GetComponent<Transform>(entity), &m_coordinator.lock()->GetComponent<SpriteRenderer>(entity), m_coordinator.lock()->GetComponent<Tag>(entity).id);
		}
	}
}	