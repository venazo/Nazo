#include "Titlescreen.h"

void Titlescreen::OnStart()
{

}

void Titlescreen::OnUpdate(float dt)
{
    Application* application = GetApplication();
    static float db = 5 * 60.0f;
    if(application->GetInput()->IsKeyPressed(GLFW_KEY_SPACE) && db >= 5 * 60.0f)
    {
        db = 0.0f;
        application->GetSceneManager()->SetActiveScene("assets/scenes/Game.zs");
    }

    db += dt;
}

void Titlescreen::OnDestroy()
{

}

Titlescreen::~Titlescreen()
{

}

std::shared_ptr<Titlescreen> Titlescreen::Create()
{
    return std::make_shared<Titlescreen>();
}