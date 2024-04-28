#include <zpch.h>
#include "SceneManager.h"
#include "Scene.h"
#include "SceneSerializer.h"

namespace Zewada {

	SceneManager::SceneManager(Application* application)
	{
		m_application = application;
		m_sceneSerializer = std::make_shared<SceneSerializer>();
		m_sceneSerializer->DeserializeAssets(m_application->GetAssetPool());
		m_sceneLoading = std::future<std::shared_ptr<Scene>>();
		m_sceneSaving = std::future<void>();
	}
	
	SceneManager::~SceneManager()
	{
		
	}
	
	void SceneManager::CreateDefaultScene()
	{
		SetActiveScene("assets/scenes/Default_Scene.zs");
	}

	void SceneManager::OnStart()
	{
		m_scenes.front()->OnStart();
	}

	void SceneManager::OnStop()
	{
		m_scenes.front()->OnStop();
	}

	void SceneManager::OnRuntimeUpdate(float dt)
	{	
		if(m_sceneLoading._Is_ready())
		{
			if(m_scenes.size() > 0)
			{
				m_scenes.front()->OnStop();
				m_scenes.pop();
			}

			m_scenes.push(m_sceneLoading.get());
			m_sceneLoading = std::future<std::shared_ptr<Scene>>();
			m_scenes.front()->Init(m_application);

			ChangedSceneEvent event(m_scenes.front());
			m_callback(event);
			m_scenes.front()->OnStart();
			m_scenes.front()->OnRuntimeUpdate(dt);
			return;
		}
		
		if(m_scenes.size() > 0)
			m_scenes.front()->OnRuntimeUpdate(dt);
	}

	void SceneManager::OnUpdate(float dt)
	{
		if(m_sceneLoading._Is_ready())
		{
			if(m_scenes.size() > 0)
			{
				m_scenes.front()->Destroy();
				m_scenes.pop();
			}
		
			m_scenes.push(m_sceneLoading.get());
			m_sceneLoading = std::future<std::shared_ptr<Scene>>();
			m_scenes.front()->Init(m_application);

			ChangedSceneEvent event(m_scenes.front());
			m_callback(event);
			m_scenes.front()->OnUpdate(dt);
			return;
		}
		
		if(m_scenes.size() > 0)
			m_scenes.front()->OnUpdate(dt);
	}

	void SceneManager::OnRender()
	{
		if(m_scenes.size() > 0)
			m_scenes.front()->OnRender();
	}

	void SceneManager::SaveActiveScene()
	{
		if(m_sceneLoading._Ptr() == nullptr)
		{
			m_scenes.front()->Save();
			std::shared_ptr<Scene> scene = std::make_shared<Scene>(*m_scenes.front().get());
			m_sceneSaving = std::move(std::async(std::launch::async, &SceneSerializer::Serialize, *m_sceneSerializer, scene));	
		}
	}

	void SceneManager::SetActiveScene(const std::string path)
	{
		if(m_sceneLoading._Ptr() == nullptr)
			m_sceneLoading = std::move(std::async(std::launch::async, &SceneSerializer::Deserialize, *m_sceneSerializer, path));
	}

	void SceneManager::SetEventCallback(const EventCallbackFn& callback)
	{
		m_callback = callback;
	}
}
