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
        m_world = nullptr;
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
        if(!go->HasCollider())
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

        b2Shape* shape;

        if(go->HasComponent<Box2DCollider>())
        {
            b2PolygonShape* box = new b2PolygonShape();
            Box2DCollider& boxCollider = go->GetComponent<Box2DCollider>();
            const glm::vec2& halfSize = boxCollider.halfSize * 0.5f;
            const glm::vec2& offset = boxCollider.offset;
            box->SetAsBox(halfSize.x, halfSize.y, b2Vec2(0.0f, 0.0f), 0);

            b2Vec2& pos = bodyDef.position;
            float xPos = pos.x + offset.x;
            float yPos = pos.y + offset.y;
            bodyDef.position.Set(xPos, yPos);
            
            AddFixture(bodyDef, box, go);
        }
        
        if(go->HasComponent<Circle2DCollider>())
        {
            b2CircleShape* circle = new b2CircleShape();
            auto& circleCollider = go->GetComponent<Circle2DCollider>();
            const glm::vec2& offset = circleCollider.offset;
            circle->m_radius = circleCollider.radius;

            b2Vec2& pos = bodyDef.position;
            float xPos = pos.x + offset.x;
            float yPos = pos.y + offset.y;
            bodyDef.position.Set(xPos, yPos);

            AddFixture(bodyDef, circle, go);
        }

        if(go->HasComponent<Edge2DCollider>())
        {
            b2ChainShape* edge = new b2ChainShape();
            auto& edgeCollider = go->GetComponent<Edge2DCollider>();
            const glm::vec2& offset = edgeCollider.offset;

            b2Vec2* vertices;
            int count = 0;
            if(edgeCollider.vertices.size() > 1)
            {
                count = edgeCollider.vertices.size();
                vertices = new b2Vec2[count];
                for(int i = 0; i < count; i++)
                {   
                    vertices[i] = b2Vec2(edgeCollider.vertices[i].x, edgeCollider.vertices[i].y);
                }
            }
            if(count == 0)
            {
                count = 3;
                vertices = new b2Vec2[count];
                vertices[0] = b2Vec2(-0.5f, 0.0f);
                vertices[1] = b2Vec2(0.5f, 0.0f);
                vertices[2] = b2Vec2(0.0f, 0.5f);

                Z_INFO() << "Default edgeCollider created.";
            }

            b2Vec2 previousGhost = b2Vec2(edgeCollider.previousGhostVertex.x, edgeCollider.previousGhostVertex.y);
            b2Vec2 nextGhost = b2Vec2(edgeCollider.nextGhostVertex.x, edgeCollider.nextGhostVertex.y);

            edge->CreateChain(vertices, count, previousGhost, nextGhost);

            b2Vec2& pos = bodyDef.position;
            float xPos = pos.x + offset.x;
            float yPos = pos.y + offset.y;
            bodyDef.position.Set(xPos, yPos);

            AddFixture(bodyDef, edge, go);
        }

        if(go->HasComponent<Polygon2DCollider>())
        {
            b2PolygonShape* polygon = new b2PolygonShape();
            auto& polygonCollider = go->GetComponent<Polygon2DCollider>();
            const glm::vec2& offset = polygonCollider.offset;
            b2Vec2* vertices;
            int count = 0;
            
            if(polygonCollider.vertices.size() > 2)
            {
                count = polygonCollider.vertices.size();
                vertices = new b2Vec2[count];
                for(int i = 0; i < count; i++)
                {
                    vertices[i] = b2Vec2(polygonCollider.vertices[i].x, polygonCollider.vertices[i].y);
                }
            }
            if(count == 0)
            {
                count = 3;
                vertices = new b2Vec2[count];
                vertices[0] = b2Vec2(-15.0f, 0.0f);
                vertices[1] = b2Vec2(15.0f, 0.0f);
                vertices[2] = b2Vec2(0.0f, 15.0f);
                Z_INFO() << "Default polygonCollider created.";
            }

            polygon->Set(vertices, count);

            b2Vec2& pos = bodyDef.position;
            float xPos = pos.x + offset.x;
            float yPos = pos.y + offset.y;
            bodyDef.position.Set(xPos, yPos);

            AddFixture(bodyDef, polygon, go);
        }
    }

    void Physics2D::AddFixture(const b2BodyDef& bodyDef, b2Shape* shape, GameObject* go)
    {
        Rigidbody2D& rb = go->GetComponent<Rigidbody2D>();

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

        if(go.HasCollider())
        {
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

    bool Physics2D::RaycastLine(const glm::vec2& first, const glm::vec2& second)
    {
        b2RayCastInput input;
        input.p1 = b2Vec2(first.x, first.y);
        input.p2 = b2Vec2(second.x, second.y);
        input.maxFraction = 1;
  
        float closestFraction = 1; 
        b2Vec2 intersectionNormal(0,0);
        for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext()) {
            for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {
                b2RayCastOutput output;
                if (f->RayCast(&output, input, 0))
                {
                    return true;
                }
            }            
        }
        return false;
    }
}   