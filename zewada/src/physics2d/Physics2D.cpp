#include <zpch.h>
#include "Physics2D.h"
#include "../scene/Scene.h"
#include "../scene/GameObject.h"
#include "ContactListener.h"

namespace Zewada {    

    std::unordered_map<BodyType, std::string> bodyType2Names = 
    {
        {BodyType::Static, "Static"},
        {BodyType::Dynamic, "Dynamic"},
        {BodyType::Kinematic, "Kinematic"}
    };

    std::unordered_map<std::string, BodyType> names2BodyType =
    {
        {"Static", BodyType::Static},
        {"Dynamic", BodyType::Dynamic},
        {"Kinematic", BodyType::Kinematic}
    };
    
    Physics2D::Physics2D(std::shared_ptr<SceneManager> sceneManager)
    {
        m_sceneManager = sceneManager;
        m_contactListener = std::make_shared<ContactListener>(sceneManager);
    }
    
    void Physics2D::OnStart()
    {
        m_world = new b2World(m_gravity);
        m_world->SetContactListener(m_contactListener.get());
    }

    void Physics2D::OnUpdate(float dt)
    {
        m_physicsTime += dt;
        if(m_physicsTime >= 0.0f)
        {
            m_physicsTime -= m_physicsTimeStep;
            m_world->Step(m_physicsTimeStep, m_velocityIterations, m_positionIterations);
        }
    }

    void Physics2D::OnStop()
    {
        delete m_world;
        m_world = nullptr;
    }

    void Physics2D::Add(const Entity& entity)
    {
        GameObject* go = new GameObject(entity, m_sceneManager->GetActiveScene());
        if(!go->HasComponent<Rigidbody2D>())
        {
            return;
        }
        if(!go->HasComponent<Box2DCollider>())
        {
            return;
        }
        Transform& transform = go->GetComponent<Transform>();
        b2BodyDef bodyDef = b2BodyDef();
        bodyDef.angle = transform.rotation * (M_PI / 180.0f);
        bodyDef.position.Set(transform.pos.x, transform.pos.y);
        Rigidbody2D& rb = go->GetComponent<Rigidbody2D>();
        bodyDef.angularDamping = rb.angularDamping;
        bodyDef.linearDamping = rb.linearDamping;
        bodyDef.fixedRotation = rb.fixedRotation;
        bodyDef.bullet = rb.continuousCollision;
        bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(go);

        switch(rb.bodyType)
        {
            case Kinematic:
                bodyDef.type = b2_kinematicBody; break;
            case Static:
                bodyDef.type = b2_staticBody; break;
            case Dynamic:
                bodyDef.type = b2_dynamicBody; break;
        }

        b2PolygonShape* shape = new b2PolygonShape();
        if(go->HasComponent<Box2DCollider>())
        {
            Box2DCollider& boxCollider = go->GetComponent<Box2DCollider>();
            const glm::vec2& halfSize = boxCollider.halfSize * 0.5f;
            const glm::vec2& offset = boxCollider.offset;
            const glm::vec2& origin = boxCollider.origin;
            shape->SetAsBox(halfSize.x, halfSize.y, b2Vec2(origin.x, origin.y), 0);

            b2Vec2& pos = bodyDef.position;
            float xPos = pos.x + offset.x;
            float yPos = pos.y + offset.y;
            bodyDef.position.Set(xPos, yPos);
        }

        b2Body* body = m_world->CreateBody(&bodyDef);
        rb.rawBody = body;

        b2FixtureDef* fixtureDef = new b2FixtureDef();
        fixtureDef->shape = shape;
        fixtureDef->density = 1.0f;
        fixtureDef->friction = rb.mass;
        fixtureDef->userData.pointer = reinterpret_cast<uintptr_t>(go);
        //fixtureDef->isSensor = rb.isSensor();
        body->CreateFixture(fixtureDef);
    }

    void Physics2D::SetGravity(float x, float y)
    {
        m_gravity.x = x;
        m_gravity.y = y;
    }

    void Physics2D::DestroyEntity(const Entity& entity)
    {
        if(m_world == nullptr)
        {
            return;
        }
        GameObject go = GameObject(entity, m_sceneManager->GetActiveScene());
		Rigidbody2D& rigidbody = go.GetComponent<Rigidbody2D>();
        //delete (GameObject*)rigidbody.rawBody->GetUserData().pointer;
        delete (GameObject*)rigidbody.rawBody->GetFixtureList()->GetUserData().pointer;
        GameObject* nullObject = GameObject::GetNullObject();
        rigidbody.rawBody->GetFixtureList()->GetUserData().pointer = (uintptr_t)nullObject;
		if(rigidbody.rawBody != nullptr)
		{
            m_world->DestroyBody(rigidbody.rawBody);
            rigidbody.rawBody = nullptr;
		}
    }
}   