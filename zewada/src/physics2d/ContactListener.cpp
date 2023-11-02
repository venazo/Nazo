#include "ContactListener.h"
#include "../scene/GameObject.h"
#include "../scene/ScriptableEntity.h"

namespace Zewada
{
    ContactListener::ContactListener(std::shared_ptr<SceneManager> sceneManager)
    {
        m_sceneManager = sceneManager;
    }

    void ContactListener::BeginContact(b2Contact* contact)
    {
        GameObject* objA = (GameObject*)contact->GetFixtureA()->GetUserData().pointer;
        GameObject* objB = (GameObject*)contact->GetFixtureB()->GetUserData().pointer;

        b2WorldManifold* worldmanifold = new b2WorldManifold();
        contact->GetWorldManifold(worldmanifold);
        glm::vec2 aNormal = glm::vec2(worldmanifold->normal.x, worldmanifold->normal.y);
        glm::vec2 bNormal = glm::vec2(aNormal.x * -1.0f, aNormal.y * -1.0f);
        if(objA->HasComponent<NativeScript>())
        {
            auto& ns = objA->GetComponent<NativeScript>();
            if(ns.className != "NONE")
            {
                ns.script->OnBeginContact(aNormal);
            }
        }
        if(objB->HasComponent<NativeScript>())
        {
            auto& ns = objB->GetComponent<NativeScript>();
            if(ns.className != "NONE")
            {
                ns.script->OnBeginContact(bNormal);
            }
        }
    }

    void ContactListener::EndContact(b2Contact* contact)
    {
        GameObject* objA = (GameObject*)contact->GetFixtureA()->GetUserData().pointer;
        GameObject* objB = (GameObject*)contact->GetFixtureB()->GetUserData().pointer;

        b2WorldManifold* worldmanifold = new b2WorldManifold();
        contact->GetWorldManifold(worldmanifold);
        glm::vec2 aNormal = glm::vec2(worldmanifold->normal.x, worldmanifold->normal.y);
        glm::vec2 bNormal = glm::vec2(aNormal.x * -1.0f, aNormal.y * -1.0f);
        
        //check if object was deleted to break contact
        if(m_sceneManager->GetActiveScene()->Exist(objA->GetID()))
        {
            if(objA->HasComponent<NativeScript>())
            {
                auto& ns = objA->GetComponent<NativeScript>();
                if(ns.className != "NONE")
                {
                    ns.script->OnEndContact(aNormal);
                }
            }
        }

        if(m_sceneManager->GetActiveScene()->Exist(objB->GetID()))
        {
            if(objB->HasComponent<NativeScript>())
            {
                auto& ns = objB->GetComponent<NativeScript>();
                if(ns.className != "NONE")
                {
                    ns.script->OnEndContact(bNormal);
                }
            }
        }

    }
}