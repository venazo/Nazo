#include <zpch.h>
#include "Scene.h"

#include "GameObject.h"
#include "../Scene/ScriptableEntity.h"


namespace Zewada
{

#define BIND_EVENT_FN(x) std::bind(&Zewada::Scene::x, this, std::placeholders::_1)

	void Scene::Init()
	{
		m_coordinator = std::make_shared<Coordinator>();

		m_coordinator->RegisterComponent<Tag>();
		m_coordinator->RegisterComponent<Transform>();
		m_coordinator->RegisterComponent<SpriteRenderer>();
		m_coordinator->RegisterComponent<Camera>();
		m_coordinator->RegisterComponent<UnSerializable>();
		m_coordinator->RegisterComponent<Rigidbody2D>();
		m_coordinator->RegisterComponent<Box2DCollider>();
		m_coordinator->RegisterComponent<NativeScript>();

		m_transformSystem = m_coordinator->RegisterSystem<TransformSystem>();

		Signature transformSystemSignature;
		transformSystemSignature.set(m_coordinator->GetComponentType<Transform>());
		m_coordinator->SetSystemSignature<TransformSystem>(transformSystemSignature);

		m_transformSystem->Init(this->shared_from_this(), m_coordinator);

		m_spriteRendererSystem = m_coordinator->RegisterSystem<SpriteRendererSystem>();

		Signature spriteRendererSignature;
		spriteRendererSignature.set(m_coordinator->GetComponentType<SpriteRenderer>());
		m_coordinator->SetSystemSignature<SpriteRendererSystem>(spriteRendererSignature);

		m_spriteRendererSystem->Init(this->shared_from_this(), m_coordinator);

		m_cameraSystem = m_coordinator->RegisterSystem<CameraSystem>();

		Signature cameraSystemSignature;
		cameraSystemSignature.set(m_coordinator->GetComponentType<Camera>());
		m_coordinator->SetSystemSignature<CameraSystem>(cameraSystemSignature);

		m_cameraSystem->Init(this->shared_from_this(), m_coordinator);

		m_rigidBody2Dsystem = m_coordinator->RegisterSystem<Rigidbody2DSystem>();

		Signature rigidBody2DSystemSignature;
		rigidBody2DSystemSignature.set(m_coordinator->GetComponentType<Rigidbody2D>());
		m_coordinator->SetSystemSignature<Rigidbody2DSystem>(rigidBody2DSystemSignature);

		m_rigidBody2Dsystem->Init(this->shared_from_this(), m_coordinator);
		
		m_nativeScriptSystem = m_coordinator->RegisterSystem<NativeScriptSystem>();

		Signature nativeScriptSystemSignature;
		nativeScriptSystemSignature.set(m_coordinator->GetComponentType<NativeScript>());
		m_coordinator->SetSystemSignature<NativeScriptSystem>(nativeScriptSystemSignature);

		m_nativeScriptSystem->Init(this->shared_from_this(), m_coordinator);

		m_physics2D = m_application->GetPhysics2D();
	}

	Scene::Scene(const std::string &path, Application* application)
	{
		m_application = application;
		m_path = path;

		m_application = application;
		for (int i = 0; i < MAX_ENTITIES; i++)
		{
			m_ids.push_back(i);
		}
		m_ID2Entity.insert({-1, -1});
	}

	Scene::~Scene()
	{

	}

	void Scene::OnStart()
	{
		m_physics2D->OnStart();
		for (auto &entity : m_coordinator->GetAllEntities())
		{
			m_physics2D->Add(entity);
		}
		m_nativeScriptSystem->OnStart();
	}

	void Scene::OnStop()
	{
		Destroy();
		m_physics2D->OnStop();
	}
	
	void Scene::OnRuntimeUpdate(float dt)
	{
		m_cameraSystem->OnUpdate(dt);
		
		m_nativeScriptSystem->OnUpdate(dt);
		m_physics2D->OnUpdate(dt);
		m_rigidBody2Dsystem->OnUpdate(dt);

		//last systems
		m_transformSystem->OnUpdate(dt);
		m_spriteRendererSystem->OnUpdate(dt);
	}

	void Scene::OnUpdate(float dt)
	{
		m_cameraSystem->OnUpdate(dt);
		m_transformSystem->OnUpdate(dt);

		m_spriteRendererSystem->OnUpdate(dt);
	}

	void Scene::OnRender()
	{
		if (m_cameraSystem->HasMainCamera())
			m_application->GetRenderer2D()->Render(m_cameraSystem->GetMaincamera());
	}

	void Scene::OnResize(WindowResizeEvent &event)
	{
		m_cameraSystem->Resize(event.GetWidth(), event.GetHeight());
	}

	Entity Scene::CreateEntity(std::string name)
	{
		Entity entity = m_coordinator->CreateEntity();
		m_coordinator->AddComponent<Tag>(Tag(name, m_ids.back()), entity);
		m_ID2Entity.insert({m_ids.back(), entity});
		m_ids.pop_back();
		m_coordinator->AddComponent<Transform>(Transform(), entity);
		return entity;
	}

	Entity Scene::CreateEntity(std::string name, ID id)
	{
		Entity entity = m_coordinator->CreateEntity();
		m_coordinator->AddComponent<Tag>(Tag(name, id), entity);
		m_ids.erase(std::remove(m_ids.begin(), m_ids.end(), id), m_ids.end());
		m_ID2Entity.insert({id, entity});
		m_coordinator->AddComponent<Transform>(Transform(), entity);
		return entity;
	}

	void Scene::Destroy()
	{
		const std::vector<Entity> &entities = m_coordinator->GetAllEntities();
		int i = 0;
		while (entities.size() > 0)
		{
			GameObject go = GameObject(entities[i], this->shared_from_this());
			Transform &transform = go.GetComponent<Transform>();
			if (transform.parent == -1)
				DestroyEntity(entities[i]);
			else
				i++;
		}
	}

	void Scene::DestroyEntity(Entity entity)
	{
		if (entity == -1)
		{
			Z_INFO("Tried to destroy -1 entitiy!");
			return;
		}
		GameObject go = GameObject(entity, this->shared_from_this());
		Transform &transform = go.GetComponent<Transform>();
		m_ids.push_back(go.GetComponent<Tag>().id);
		if (transform.parent != -1)
		{
			GameObject parent = GameObject(GetEntity(transform.parent), this->shared_from_this());
			std::vector<ID> &children = parent.GetComponent<Transform>().children;
			children.erase(remove(children.begin(), children.end(), go.GetComponent<Tag>().id), children.end());
		}

		//delete data of gameObject
		if(go.HasComponent<NativeScript>())
		{
			if(go.GetComponent<NativeScript>().script.get() != nullptr)
			{
				go.GetComponent<NativeScript>().script->OnDestroy();
				go.GetComponent<NativeScript>().script.reset();
			}
		}

		if(go.HasComponent<Camera>())
			GetCameraSystem()->DestroyEntity(go.GetID());
		if(go.HasComponent<Rigidbody2D>())
			m_application->GetPhysics2D()->DestroyEntity(go.GetID());

		
		std::vector<ID> &goChildren = transform.children;
		for (auto &child : goChildren)
		{
			DestroyEntity(GetEntity(child));
		}
		m_ID2Entity.erase(go.GetComponent<Tag>().id);
		m_coordinator->DestroyEntity(entity);
	}

	void Scene::SetPath(const std::string &path)
	{
		m_path = path;
	}

	Entity Scene::GetEntity(ID id)
	{
		
		bool result = false;
		for (auto& pair : m_ID2Entity)
		{
			if (pair.first == id)
				result = true;
		}

		if (result)
		{
			return m_ID2Entity[id];
		}
		else
		{
			return -1;
		}
	}

	bool Scene::Exist(Entity entity) const
	{
		for(auto id : m_ID2Entity)
		{
			if(id.second == entity)
				return true;
		}
		return false;
	}
}