#pragma once

#include <boost/dll.hpp>
#include <boost/config.hpp>
#include <boost/dll/alias.hpp>
#include <Zewada.h>

using namespace Zewada;

class Titlescreen : public ScriptableEntity
{
public:
    ~Titlescreen();

    void OnStart() override;
    void OnUpdate(float dt) override;
    void OnDestroy() override;
    
    static std::shared_ptr<Titlescreen> Create();
};

BOOST_DLL_ALIAS(Titlescreen::Create, SCRIPT_Titlescreen)