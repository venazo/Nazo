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
        y += 100.0f;
    }
    if(application->GetInput()->IsKeyPressed(GLFW_KEY_S))
    {
        y -= 100.0f;
    }
    if(application->GetInput()->IsKeyPressed(GLFW_KEY_D))
    {
        x += 100.0f;
    }
    if(application->GetInput()->IsKeyPressed(GLFW_KEY_A))
    {
        x -= 100.0f;
    }

    GetGameObject().ApplyImpulse(glm::vec2(x, y));
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
