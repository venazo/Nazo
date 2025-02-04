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
			SetPosition((pos - parentPos));
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
				scale.x *= 1/(width*P2M);
				scale.y *= 1/(height*P2M);
            }
			transform.scale += scale;
        }
	}

	void GameObject::SetWorldScale(float x, float y)
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
				scale.x *= 1/(width*P2M);
				scale.y *= 1/(height*P2M);
            }
			transform.scale = scale;
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
			GameObject parent(m_scene->GetEntity(newChild.GetComponent<Transform>().parent), m_scene);
			auto& oldChildren = parent.GetComponent<Transform>().children;
			oldChildren.erase(std::remove(oldChildren.begin(), oldChildren.end(), newChild.GetComponent<Tag>().id), oldChildren.end());
			newChild.GetComponent<Transform>().parent = result.GetComponent<Tag>().id;
			newChildren.push_back(newChild.GetComponent<Tag>().id);
		}
		children = newChildren;
		auto id = result.GetComponent<Transform>().parent;
		if(id != -1)
		{
			GameObject parent(m_scene->GetEntity(id), m_scene);
			parent.GetComponent<Transform>().children.push_back(result.GetComponent<Tag>().id);
		}

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
		if(HasComponent<Circle2DCollider>())
		{
			result.AddComponent<Circle2DCollider>(Circle2DCollider(GetComponent<Circle2DCollider>()));
		}
		if(HasComponent<Edge2DCollider>())
		{
			result.AddComponent<Edge2DCollider>(Edge2DCollider(GetComponent<Edge2DCollider>()));
		}
		if(HasComponent<Polygon2DCollider>())
		{
			result.AddComponent<Polygon2DCollider>(Polygon2DCollider(GetComponent<Polygon2DCollider>()));
		}
		if(HasComponent<NativeScript>())
		{
			result.AddComponent<NativeScript>(NativeScript(GetComponent<NativeScript>()));
			result.GetComponent<NativeScript>().script = nullptr;
		}
		if(HasComponent<Animation>())
		{
			result.AddComponent<Animation>(Animation(GetComponent<Animation>()));
		}
		if(HasComponent<AnimationManager>())
		{
			result.AddComponent<AnimationManager>(AnimationManager(GetComponent<AnimationManager>()));
		}
		if(HasComponent<Text>())
		{
			result.AddComponent<Text>(Text(GetComponent<Text>()));
		}

		//obsolete
		/*if(HasComponent<Grid>())
		{
			result.AddComponent<Grid>(Grid(GetComponent<Grid>()));
		}
		if(HasComponent<GridObject>())
		{
			result.AddComponent<GridObject>(GridObject(GetComponent<GridObject>()));
			GameObject grid(m_scene->GetEntity(GetComponent<Transform>().parent), m_scene);
			grid.GetComponent<Transform>().children.push_back(result.GetComponent<Tag>().id);
		}*/
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
		if(!HasComponent<Rigidbody2D>() || !HasCollider())
		{
			return;
		}

		b2Vec2 vec = b2Vec2(x, y) ;
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
		if(!HasComponent<Rigidbody2D>() || !HasCollider())
		{
			return;
		}

		b2Vec2 vec = b2Vec2(x, y);
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
		if(!HasComponent<Rigidbody2D>() || !HasCollider())
		{
			return;
		}

		auto& rb = GetComponent<Rigidbody2D>();
		auto body = rb.rawBody;
		body->ApplyTorque(torque, true);
	}

	void GameObject::SetAnimation(const std::string& animation)
	{
		if(HasComponent<AnimationManager>())
		{
			auto& am = GetComponent<AnimationManager>();
			am.activeAnimation = animation;
			am.animations[am.activeAnimation].dt = 0.0f;
			am.animations[am.activeAnimation].activeFrame = 0;
		}
	}

	bool GameObject::HasCollider()
	{
		return (HasComponent<Box2DCollider>() || HasComponent<Circle2DCollider>() || HasComponent<Edge2DCollider>() || HasComponent<Polygon2DCollider>());
	}
}