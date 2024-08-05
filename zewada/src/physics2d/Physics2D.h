#pragma once

#include <box2d/box2d.h>
#include "BodyType.h"
#include "../ECS/core/Coordinator.h"
#include <glm/glm.hpp>
#include "../scene/SceneManager.h"
#include "../utils/debug/Logger.h"

namespace Zewada {

    class ContactListener;
    class GameObject;

    class Physics2D
    {
    private:
        b2Vec2 m_gravity = b2Vec2(0, -10.0f);
        b2World* m_world;

        std::shared_ptr<SceneManager> m_sceneManager;
        std::shared_ptr<ContactListener> m_contactListener;

        float m_physicsTime = 0.0f;
        float m_physicsTimeStep = 1.0f / 60.0f;
        int m_velocityIterations = 8;
        int m_positionIterations = 3;

        void AddFixture(const b2BodyDef& bodyDef, b2Shape* shape, GameObject* go);
    public:
        Physics2D(std::shared_ptr<SceneManager> sceneManager);

        void Add(const Entity& entity);
        void OnUpdate(float dt);
        void OnStop();
        void OnStart();
        void DestroyEntity(const Entity& entity);

        bool RaycastLine(const glm::vec2& first, const glm::vec2& second);

        inline b2World* GetWorld() { return m_world; }
        void SetGravity(float x, float y);
        inline glm::vec2 GetGravity() {return glm::vec2(m_gravity.x, m_gravity.y);}
    };
}