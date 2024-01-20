#include "AnimationManagerSystem.h"
#include "../../scene/scene.h"
#include "../Components.h"
#include "../../scene/SceneManager.h"
#include "../../scene/GameObject.h"

namespace Zewada
{
    void AnimationManagerSystem::Init(std::shared_ptr<Scene> scene, std::shared_ptr<Coordinator> coordinator)
	{
		m_scene = scene;
		m_coordinator = coordinator;

		for(Entity entity : m_entities)
		{
			GameObject go(entity, m_scene);
            auto& ac = go.GetComponent<AnimationManager>();
            for(auto& animation : ac.animations)
            {
                for(auto& frame : animation.second.frames)
                {
                    if(frame.sprite->HasTextureToLoad())
                    {
                        frame.sprite->LoadTexture(scene->GetApplication()->GetAssetPool());
                    }
                }   
            }
		}
	}

    void AnimationManagerSystem::OnStart()
    {
        for(Entity entity : m_entities)
        {
            GameObject go(entity, m_scene);
            go.AddComponent<Animation>();
        }
    }

    void AnimationManagerSystem::OnUpdate(float dt)
    {
        for(auto& entity : m_entities)
        {
            GameObject go(entity, m_scene);
            auto& animationManager = go.GetComponent<AnimationManager>();
            auto& animation = go.GetComponent<Animation>();
            if(animationManager.activeAnimation != "" && animationManager.animations.size() > 0)
                animation = animationManager.animations[animationManager.activeAnimation];
        }
    }
}