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
            GameObject go = GameObject(entity, m_scene);
            auto& rb = go.GetComponent<Rigidbody2D>();
            b2Body* rawBody = rb.rawBody;
            if(rawBody)
            {
                Transform& transform = go.GetComponent<Transform>();
                go.SetWorldPos(rawBody->GetPosition().x, rawBody->GetPosition().y);
                transform.rotation = rawBody->GetAngle() * (180.0f / M_PI);
            }
        }
    }
}