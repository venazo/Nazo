#include <zpch.h>
#include "Rigidbody2DSystem.h"
#include "../../scene/GameObject.h"
#include "../../scene/Scene.h"

namespace Zewada {
    Rigidbody2DSystem::Rigidbody2DSystem()
    {

    }

    void Rigidbody2DSystem::OnUpdate(float dt) 
    {
        for(auto& entity : m_entities)
        {
            GameObject go = GameObject(entity, m_scene.lock());
            auto& rb = go.GetComponent<Rigidbody2D>();
            b2Body* rawBody = rb.rawBody;
            if(rawBody)
            {
                Transform& transform = go.GetComponent<Transform>();
                transform.pos.x = rawBody->GetPosition().x;
                transform.pos.y = rawBody->GetPosition().y;
                transform.rotation = rawBody->GetAngle() * (180.0f / M_PI);
            }
        }
    }
}