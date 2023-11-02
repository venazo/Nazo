#pragma once

#include "../scene/SceneManager.h"
#include <box2d/box2d.h>

namespace Zewada
{
    class ContactListener : public b2ContactListener
    {
    private:
        std::shared_ptr<SceneManager> m_sceneManager;
    public:
        ContactListener(std::shared_ptr<SceneManager> sceneManager);
        void BeginContact(b2Contact* contact) override;
        void EndContact(b2Contact* contact) override;

    };
}