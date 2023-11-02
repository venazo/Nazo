#include <zpch.h>
#include "GameObject.h"

namespace Zewada {
	GameObject::~GameObject()
	{
		
	}

	GameObject::GameObject(Entity entity, std::shared_ptr<Scene> scene)
		:m_entity(entity), m_scene(scene)
	{
		m_coordinator = m_scene.lock()->GetCoordinator();
	}
	
	void GameObject::Destroy()
	{
		GetComponent<Transform>().destroyed = true;
	}

	void GameObject::SetWorldPos(const glm::vec3& pos)
	{
		GameObject parent = GameObject(GetComponent<Transform>().parent, m_scene.lock());
		if(parent.operator bool())
		{
			glm::vec3 parentPos = parent.GetComponent<Transform>().worldPos;
			GetComponent<Transform>().pos = pos - parentPos;
		}
		else
		{
			GetComponent<Transform>().pos = pos;
		}
	}

	void GameObject::AddWorldScale(float x, float y)
	{
		glm::vec2 scale(x, y);
        Transform& transform = GetComponent<Transform>();
        if(HasComponent<SpriteRenderer>())
        {
            auto sprite = GetComponent<SpriteRenderer>().sprite;
            auto tex = sprite->GetTexture();
            if(tex->GetID() != 0)
            {
                float height = tex->GetHeight();
                float width = tex->GetWidth();
                auto coords = sprite->GetUV();
                width *= abs(coords[0].x - coords[2].y);
                height *= abs(coords[1].y - coords[3].y);
				scale.x *= 1/width;
				scale.y *= 1/height;
            }
			transform.scale += scale;
        }
	}

	GameObject GameObject::Copy() const
	{
		GameObject result = GameObject(m_scene.lock()->CreateEntity(GetComponent<Tag>().name), m_scene.lock());
		result.GetComponent<Transform>() = Transform(GetComponent<Transform>());
		std::vector<Entity>& children = result.GetComponent<Transform>().children;
		std::vector<Entity> newChildren;
		for(auto child : children)
		{
			GameObject childgo = GameObject(m_scene.lock()->GetEntity(child), m_scene.lock());
			GameObject newChild = childgo.Copy();
			newChild.GetComponent<Transform>().parent = result.GetComponent<Tag>().id;
			newChildren.push_back(newChild.GetComponent<Tag>().id);
		}
		children = newChildren;
		if(HasComponent<SpriteRenderer>())
		{
			result.AddComponent<SpriteRenderer>(SpriteRenderer(GetComponent<SpriteRenderer>()));
		}
		if(HasComponent<Camera>())
		{
			result.AddComponent<Camera>(Camera(GetComponent<Camera>()));
		}
		if(HasComponent<UnSerializable>())
		{
			result.AddComponent<UnSerializable>(UnSerializable());
		}
		if(HasComponent<Rigidbody2D>())
		{
			result.AddComponent<Rigidbody2D>(Rigidbody2D(GetComponent<Rigidbody2D>()));
			result.GetComponent<Rigidbody2D>().rawBody = nullptr;
		}
		if(HasComponent<Box2DCollider>())
		{
			result.AddComponent<Box2DCollider>(Box2DCollider(GetComponent<Box2DCollider>()));
		}
		return result;
	}

	void GameObject::SetPosition(float x, float y, float z)
	{
		Transform& transform = GetComponent<Transform>();
		if(HasComponent<Rigidbody2D>())
		{
			Rigidbody2D& rb = GetComponent<Rigidbody2D>();
			rb.rawBody->SetTransform(b2Vec2(x, y), rb.rawBody->GetAngle());
		}

		transform.pos.x = x;
		transform.pos.y = y;
		transform.pos.z = z;
	}

	void GameObject::Set2DVelocity(const glm::vec2& vec)
	{
		if(HasComponent<Rigidbody2D>())
		{
			auto& rb = GetComponent<Rigidbody2D>();
			b2Vec2 velocity = b2Vec2(vec.x, vec.y);
			rb.rawBody->SetLinearVelocity(velocity);
		}
	}

    void GameObject::Set2DVelocity(float x, float y)
    {
		Set2DVelocity(glm::vec2(x, y));
    }

    void GameObject::Add2DVelocity(const glm::vec2 &vec)
    {
		if(HasComponent<Rigidbody2D>())
		{
			auto& rb = GetComponent<Rigidbody2D>();
			b2Vec2 velocity = rb.rawBody->GetLinearVelocity() + b2Vec2(vec.x, vec.y);
			rb.rawBody->SetLinearVelocity(velocity);
		}
    }

    void GameObject::Add2DVelocity(float x, float y)
    {
		Add2DVelocity(glm::vec2(x, y));
    }

	void GameObject::SetPosition(const glm::vec3& vec)
	{
		SetPosition(vec.x, vec.y, vec.z);
	}
}