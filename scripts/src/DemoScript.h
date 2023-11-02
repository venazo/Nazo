#pragma once

#include <boost/dll.hpp>
#include <boost/config.hpp>
#include <boost/dll/alias.hpp>
#include <Zewada.h>

using namespace Zewada;

class DemoScript : public ScriptableEntity
{
public:
    ~DemoScript();

    void OnUpdate(float dt) override;
    
    static std::shared_ptr<DemoScript> Create();
};


BOOST_DLL_ALIAS(DemoScript::Create, SCRIPT_DemoScript)