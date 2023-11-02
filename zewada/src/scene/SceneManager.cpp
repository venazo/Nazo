#include <zpch.h>
#include "SceneManager.h"
#include "Scene.h"
#include "../utils/resource/Serializer.h"

namespace Zewada {

	SceneManager::SceneManager(Application* application)
	{
		m_application = application;
	}
	
	void SceneManager::CreateDefaultScene()
	{
		std::shared_ptr scene = m_application->GetSerializer()->Deserialize("assets/scenes/Default_Scene.zs", m_application);
		m_scenes.push(scene);
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
		if(m_scenes.size() == 1)
			m_scenes.front()->OnRuntimeUpdate(dt);
		else
		{
			OnStop();
			m_scenes.pop();
			ChangedSceneEvent event(m_scenes.front());
			m_callback(event);
			m_scenes.front()->OnStart();
			m_scenes.front()->OnRuntimeUpdate(dt);
		}
	}

	void SceneManager::OnUpdate(float dt)
	{
		if(m_scenes.size() == 1)
			m_scenes.front()->OnUpdate(dt);
		else
		{
			OnStop();
			m_scenes.pop();
			ChangedSceneEvent event(m_scenes.front());
			m_callback(event);
			m_scenes.front()->OnUpdate(dt);
		}
	}

	void SceneManager::OnRender()
	{
		m_scenes.front()->OnRender();
	}

	void SceneManager::SetActiveScene(const std::string path)
	{
		std::shared_ptr<Scene> scene = m_application->GetSerializer()->Deserialize(path, m_application);
		m_scenes.push(scene);
	}

	void SceneManager::SetEventCallback(const EventCallbackFn& callback)
	{
		m_callback = callback;
	}
}
