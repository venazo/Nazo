#include "AnimationSystem.h"
#include "../../scene/scene.h"
#include "../Components.h"
#include "../../scene/SceneManager.h"
#include "../../scene/GameObject.h"

namespace Zewada
{
    void AnimationSystem::Init(std::shared_ptr<Scene> scene, std::shared_ptr<Coordinator> coordinator)
	{
		m_scene = scene;
		m_coordinator = coordinator;

		for(Entity entity : m_entities)
		{
			GameObject go(entity, m_scene);
            auto& ac = go.GetComponent<Animation>();
            for(auto& frame : ac.frames)
            {
                if(frame.sprite->HasTextureToLoad())
                {
                    frame.sprite->LoadTexture(scene->GetApplication()->GetAssetPool());
                }
            }
		}
	}

    void AnimationSystem::OnStart()
    {

    }

    void AnimationSystem::OnUpdate(float dt)
    {
        for(auto& entity : m_entities)
        {
            GameObject go(entity, m_scene);
            auto& animation = go.GetComponent<Animation>();
            animation.dt += dt;
            if(animation.frames.size() == 0)
                return;
            if(animation.dt >= animation.frames[animation.activeFrame].duration)
            {
                animation.activeFrame += 1;
                if(animation.activeFrame >= animation.frames.size())
                {
                    animation.activeFrame -= animation.frames.size();
                }
                animation.dt -= animation.frames[animation.activeFrame].duration;

                go.GetComponent<SpriteRenderer>().sprite = animation.frames[animation.activeFrame].sprite;
            }
        }
    }
}