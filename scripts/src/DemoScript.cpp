#include "DemoScript.h"

void DemoScript::OnStart()
{
    
}

void DemoScript::OnUpdate(float dt)
{
    static float dbounce = 0.0f;
    Application* application = GetApplication();
    const auto& transform = GetComponent<Transform>();
    bool touchGround = application->GetPhysics2D()->RaycastLine(glm::vec2(transform.worldPos), glm::vec2(transform.worldPos) + glm::vec2(0.0f, -0.1f - (transform.worldScale.y / 2.0f)));
    if(touchGround)
        dbounce += dt;
    float x = 0.0f;
    float y = 0.0f;
    if(application->GetInput()->IsKeyPressed(GLFW_KEY_W) && 
        touchGround &&
        dbounce > 0.05f)
    {
        GetGameObject().ApplyImpulse(glm::vec2(0.0f, 6.0f));
        dbounce = 0.0f;
    }
    if(application->GetInput()->IsKeyPressed(GLFW_KEY_D))
    {
        GetGameObject().ApplyForce(glm::vec2(4.0f, 0.0f));
    }
    if(application->GetInput()->IsKeyPressed(GLFW_KEY_A))
    {
        GetGameObject().ApplyForce(glm::vec2(-4.0f, 0.0f));
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
