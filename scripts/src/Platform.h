#pragma once

#include <boost/dll.hpp>
#include <boost/config.hpp>
#include <boost/dll/alias.hpp>
#include <Zewada.h>

using namespace Zewada;

class Platform : public ScriptableEntity
{
public:
    ~Platform();

    void OnStart() override;
    void OnUpdate(float dt) override;
    void OnDestroy() override;

    static std::shared_ptr<Platform> Create();
};

BOOST_DLL_ALIAS(Platform::Create, SCRIPT_Platform)