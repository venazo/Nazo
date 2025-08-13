#include "DemoScript.h"

void DemoScript::OnStart()
{
    
}

void DemoScript::OnUpdate(float dt)
{

}

void DemoScript::OnDestroy()
{

}

DemoScript::~DemoScript()
{

}

std::shared_ptr<DemoScript> DemoScript::Create()
{
    return std::make_shared<DemoScript>();
}
