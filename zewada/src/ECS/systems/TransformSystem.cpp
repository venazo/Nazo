#include <zpch.h>
#include "TransformSystem.h"
#include "../../Scene/Scene.h"
#include "../../scene/GameObject.h"

namespace Zewada
{
    TransformSystem::TransformSystem()
    {
        
    }

    void TransformSystem::OnUpdate(float dt)
    {
        int i = 0;
        for(auto it = m_entities.begin(); it != m_entities.end();)
        {
            GameObject go(*it, m_scene.lock());
            auto& trans = go.GetComponent<Transform>();
            if(trans.destroyed)
            {
                m_scene.lock()->DestroyEntity(*it);
                it = m_entities.begin();
                for(int j = 0; j < i; j++)
                {
                    ++it;
                }
            }
            else
            {
                ++it;
                i++;
            }
        }

        for(auto& entity : m_entities)
        {
            GameObject go = GameObject(entity, m_scene.lock());
            if(go.GetComponent<Transform>().parent == -1)
            {
                CalcPos(entity);
                CalcSize(entity);
            }
        }
    }
    
    void TransformSystem::CalcSize(Entity entity)
    {
            GameObject go = GameObject(entity, m_scene.lock());
            Transform& transform = go.GetComponent<Transform>();
        transform.worldScale = transform.scale;
        if(go.HasComponent<SpriteRenderer>( ))
        {
            auto sprite = go.GetComponent<SpriteRenderer>().sprite;
            auto tex = sprite->GetTexture();
            if(tex->GetID() != 0)
            {
                float height = tex->GetHeight();
                float width = tex->GetWidth();
                auto coords = sprite->GetUV();
                width *= abs(coords[0].x - coords[2].x);
                height *= abs(coords[1].y - coords[3].y);

                transform.worldScale.x *= width;
                transform.worldScale.y *= height;
            }
        }
    }

    void TransformSystem::CalcPos(Entity entity)
    {
        GameObject go  = GameObject(entity, m_scene.lock());
        Transform& transform = go.GetComponent<Transform>();
        transform.worldPos = transform.pos;
        if(transform.parent != -1)
        {
            GameObject parent = GameObject(go.GetScene().lock()->GetEntity(transform.parent), m_scene.lock());
            transform.worldPos += parent.GetComponent<Transform>().worldPos;
        }

        for(auto& child : transform.children)
        {
            CalcPos(go.GetScene().lock()->GetEntity(child));
        }
    }
}