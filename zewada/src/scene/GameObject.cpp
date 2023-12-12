#include <zpch.h>
#include "GameObject.h"

namespace Zewada {
	GameObject::~GameObject()
	{
		
	}

	GameObject::GameObject(Entity entity, std::shared_ptr<Scene> scene)
		:m_entity(entity), m_scene(scene)
	{
		m_coordinator = m_scene->GetCoordinator();
	}
	
	void GameObject::Destroy()
	{
		GetComponent<Transform>().destroyed = true;
	}

	void GameObject::SetWorldPos(float x, float y, float z)
	{
		SetWorldPos(glm::vec3(x, y, z));
	}

	void GameObject::SetWorldPos(const glm::vec3& pos)
	{
		GameObject parent = GameObject(m_scene->GetEntity(GetComponent<Transform>().parent), m_scene);
		if(parent.operator bool())
		{
			glm::vec3 parentPos = parent.GetComponent<Transform>().worldPos;
			SetPosition(pos - parentPos);
		}
		else
		{
			SetPosition(pos);
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
		GameObject result = GameObject(m_scene->CreateEntity(GetComponent<Tag>().name), m_scene);
		result.GetComponent<Transform>() = Transform(GetComponent<Transform>());
		std::vector<Entity>& children = result.GetComponent<Transform>().children;
		std::vector<Entity> newChildren;
		for(auto child : children)
		{
			GameObject childgo = GameObject(m_scene->GetEntity(child), m_scene);
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
			GetComponent<Rigidbody2D>().rawBody->SetTransform(b2Vec2(x, y), transform.rotation / 180.0f * M_PI);
		}

		transform.pos.x = x;
		transform.pos.y = y;
		transform.pos.z = z;
	}

	void GameObject::SetPosition(const glm::vec3& vec)
	{
		SetPosition(vec.x, vec.y, vec.z);
	}

	void GameObject::AddRotation(float r)
	{
		SetRotation(GetComponent<Transform>().rotation + r);
	}

	void GameObject::SetRotation(float r)
	{
		auto& trans = GetComponent<Transform>();
		trans.rotation = r;
		if(HasComponent<Rigidbody2D>())
		{
			GetComponent<Rigidbody2D>().rawBody->SetTransform(b2Vec2(trans.worldPos.x, trans.worldPos.y), r);
		}
	}

	GameObject* GameObject::GetNullObject()
	{ 
		static GameObject* go = new GameObject();
		return go;
	}

	void GameObject::ApplyForce(float x, float y)
	{
		if(!HasComponent<Rigidbody2D>())
		{
			Z_INFO() << "Can't apply force because gameobject doesn't have Rigidbody2D";
			return;
		}

		b2Vec2 vec = b2Vec2(x* 100.0f, y * 100.0f) ;
		auto& rb = GetComponent<Rigidbody2D>();
		auto body = rb.rawBody;
		body->ApplyForceToCenter(vec, true);
	}

	void GameObject::ApplyForce(const glm::vec2& force)
	{
		ApplyForce(force.x, force.y);
	}

	void GameObject::ApplyImpulse(float x, float y)
	{
		if(!HasComponent<Rigidbody2D>())
		{
			Z_INFO() << "Can't apply impulse because gameobject doesn't have Rigidbody2D";
			return;
		}

		b2Vec2 vec = b2Vec2(x* 100.0f, y* 100.0f);
		auto& rb = GetComponent<Rigidbody2D>();
		auto body = rb.rawBody;
		body->ApplyLinearImpulseToCenter(vec, true);
	}

	void GameObject::ApplyImpulse(const glm::vec2& impulse)
	{
		ApplyImpulse(impulse.x, impulse.y);
	}

	void GameObject::ApplyTorque(float torque)
	{
		if(!HasComponent<Rigidbody2D>())
		{
			Z_INFO() << "Can't apply torque because gameobject doesn't have Rigidbody2D";
			return;
		}

		auto& rb = GetComponent<Rigidbody2D>();
		auto body = rb.rawBody;
		body->ApplyTorque(torque, true);
	}
}