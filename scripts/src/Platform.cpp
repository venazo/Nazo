#include "platform.h"

Platform::~Platform()
{

}

void Platform::OnStart()
{
    auto* b = GetComponent<Rigidbody2D>().rawBody;

    Entity aEntity = GetGameObject().GetScene()->GetEntity(GetComponent<Transform>().parent);
    GameObject go(aEntity, GetGameObject().GetScene());

    auto* a = go.GetComponent<Rigidbody2D>().rawBody;

    b2PrismaticJointDef jointDef;
    b2Vec2 worldAxis(1.0f, 0.0f);
    jointDef.collideConnected = true;
    jointDef.Initialize(b, a,
        b->GetWorldCenter(), worldAxis);
    GetApplication()->GetPhysics2D()->GetWorld()->CreateJoint(&jointDef);
}

void Platform::OnUpdate(float dt)
{
    Application* application = GetApplication();
    auto transform = GetComponent<Transform>();
    if(application->GetInput()->IsKeyPressed(GLFW_KEY_D))
    {
        GetGameObject().ApplyForce(glm::vec2(40.0f, 0.0f));
    }
    if(application->GetInput()->IsKeyPressed(GLFW_KEY_A))
    {
        GetGameObject().ApplyForce(glm::vec2(-40.0f, 0.0f));
    }
}

void Platform::OnDestroy()
{

}

std::shared_ptr<Platform> Platform::Create()
{
    return std::make_shared<Platform>();
}