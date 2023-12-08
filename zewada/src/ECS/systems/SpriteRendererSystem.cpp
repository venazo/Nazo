#include <zpch.h>
#include "SpriteRendererSystem.h"
#include "../../scene/Scene.h"
#include "../../scene/GameObject.h"

namespace Zewada {

	void SpriteRendererSystem::Init(std::shared_ptr<Scene> scene, std::shared_ptr<Coordinator> coordinator)
	{
		m_scene = scene;
		m_coordinator = coordinator;

		for(Entity entity : m_entities)
		{
			GameObject go(entity, m_scene);
			if(go.GetComponent<SpriteRenderer>().sprite->HasTextureToLoad())
			{
				go.GetComponent<SpriteRenderer>().sprite->LoadTexture(scene->GetApplication()->GetAssetPool());
			}
		}
	}

	void SpriteRendererSystem::OnUpdate(float dt)
	{
		for (Entity entity : m_entities)
		{
			m_scene->GetApplication()->GetRenderer2D()->Submit(&m_coordinator->GetComponent<Transform>(entity), &m_coordinator->GetComponent<SpriteRenderer>(entity), m_coordinator->GetComponent<Tag>(entity).id);
		}
	}
}	