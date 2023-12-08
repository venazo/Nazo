#include "DemoScript.h"

void DemoScript::OnStart()
{
    
}

void DemoScript::OnUpdate(float dt)
{
    Application* application = GetApplication();
    float x = 0.0f;
    float y = 0.0f;
    if(application->GetInput()->IsKeyPressed(GLFW_KEY_W))
    {
        y += 10.0f;
    }
    if(application->GetInput()->IsKeyPressed(GLFW_KEY_S))
    {
        y -= 10.0f;
    }
    if(application->GetInput()->IsKeyPressed(GLFW_KEY_D))
    {
        x += 10.0f;
    }
    if(application->GetInput()->IsKeyPressed(GLFW_KEY_A))
    {
        x -= 10.0f;
    }
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
