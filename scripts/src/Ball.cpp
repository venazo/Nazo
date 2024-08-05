#include "Ball.h"

Ball::~Ball()
{

}

void Ball::OnStart()
{
    GetApplication()->GetAssetPool()->AddSound(std::make_shared<Sound>("assets/sounds/Wall.ogg", false));
    GetApplication()->GetAssetPool()->AddSound(std::make_shared<Sound>("assets/sounds/Block.ogg", false));
    float max = 1.0f;
    float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    if(0 + (rand() % (1 - 0 + 1)) == 1)
        x *= -1;

    auto* b = GetComponent<Rigidbody2D>().rawBody;

    float y = sqrt((max*max) - (x*x));
    GetGameObject().ApplyImpulse(x, y);

    b2Vec2 velocity = b->GetLinearVelocity();
    float speed = velocity.Length();  

    m_maxSpeed = speed;
}

void Ball::OnUpdate(float dt)
{   
    auto* b = GetComponent<Rigidbody2D>().rawBody;

    b2Vec2 velocity = b->GetLinearVelocity();
    float speed = velocity.Length();   

    if (speed > m_maxSpeed) {
        b->SetLinearDamping(0.05);
    } else if (speed < m_maxSpeed) {
        b->SetLinearDamping(0.0);
    }

    auto& trans = GetComponent<Transform>();

    if(trans.worldPos.y < -5.4f)
    {
        static float lWait = 0.0f;
        if(lWait < 3.0f)
        {
            lWait += dt;
        }
        else
        {
            Z_INFO() << "LOST";
            GetApplication()->GetSceneManager()->SetActiveSceneNextFrame("assets/scenes/Default_Scene.zs");
            lWait = -1000.0f;
        }
    }

    if(m_won)
    {
        static float wWait = 0.0f;
        if(wWait < 3.0f)
        {
            wWait += dt;
        }
        else
        {
            Z_INFO() << "WON";
            GetApplication()->GetSceneManager()->SetActiveSceneNextFrame("assets/scenes/Default_Scene.zs");
            wWait = -1000.0f;
        }
    }
}

void Ball::OnDestroy()
{
    GetApplication()->GetAssetPool()->RemoveSound("assets/sounds/Wall.ogg");
    GetApplication()->GetAssetPool()->RemoveSound("assets/sounds/Block.ogg");
}

void Ball::OnEndContact(const glm::vec2& hitNormal, GameObject* other)
{
    GameObject parent(other->GetScene()->GetEntity(other->GetComponent<Transform>().parent), other->GetScene());
    if(parent.GetComponent<Tag>().name != "row")
    {
        GetApplication()->GetAssetPool()->GetSound("assets/sounds/Wall.ogg")->Play();
        return;
    }
        
    GetApplication()->GetAssetPool()->GetSound("assets/sounds/Block.ogg")->Play();
    static int count = 0;
    count++;

    if(count >= 100)
    {
        m_won = true;
    }

    other->Destroy();
}

std::shared_ptr<Ball> Ball::Create()
{
    return std::make_shared<Ball>();
}