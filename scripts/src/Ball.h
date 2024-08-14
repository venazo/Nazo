#pragma once

#include <boost/dll.hpp>
#include <boost/config.hpp>
#include <boost/dll/alias.hpp>
#include <Zewada.h>
#include <ctime>

using namespace Zewada;

class Ball : public ScriptableEntity
{
private:
    float m_maxSpeed;
    bool m_won = false;
public:
    ~Ball();

    void OnStart() override;
    void OnUpdate(float dt) override;
    void OnDestroy() override;

    void OnEndContact(const glm::vec2& hitNormal, GameObject* other);

    static std::shared_ptr<Ball> Create();
};

BOOST_DLL_ALIAS(Ball::Create, SCRIPT_Ball)