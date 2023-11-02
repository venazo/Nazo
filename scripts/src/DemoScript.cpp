#include "DemoScript.h"

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
    if(application->GetInput()->IsKeyPressed(GLFW_KEY_9))
    {
        GetGameObject().Destroy();
    }
   
    GetGameObject().Set2DVelocity(x, y);
}

DemoScript::~DemoScript()
{

}

std::shared_ptr<DemoScript> DemoScript::Create()
{
    return std::make_shared<DemoScript>();
}
