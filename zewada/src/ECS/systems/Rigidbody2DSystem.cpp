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

                if(transform.parent != -1)
                {
                    GameObject parent(m_scene->GetEntity(transform.parent), m_scene);
                    glm::vec3 parentPos = parent.GetComponent<Transform>().worldPos;
                    transform.pos = glm::vec3(rawBody->GetPosition().x, rawBody->GetPosition().y, 0.0f) - parentPos;
                }
                else
                {
                    transform.pos = glm::vec3(rawBody->GetPosition().x, rawBody->GetPosition().y, 0.0f);
                }
                transform.rotation = rawBody->GetAngle() * (180.0f / M_PI);
            }
        }
    }
}