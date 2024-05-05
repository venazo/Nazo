#pragma once

#include "../Utils/Debug/Logger.h"
#include <vector>
#include <mutex>
#include <future>
#include <queue>
#include <map>

namespace Zewada {

	class Scene;
	class SceneSerializer;
	class Event;
	class Application;

	using EventCallbackFn = std::function<void(Event&)>;

	class SceneManager : public std::enable_shared_from_this<SceneManager>
	{
	private:
		std::queue<std::shared_ptr<Scene>> m_scenes;
		EventCallbackFn m_callback;

		std::future<std::shared_ptr<Scene>> m_sceneLoading;
		std::future<void> m_sceneSaving;

		Application* m_application;
		std::shared_ptr<SceneSerializer> m_sceneSerializer;

	public:
		SceneManager(Application* application);
		~SceneManager();

		void CreateDefaultScene();
		
		void OnStart();
		void OnStop();
		void OnUpdate(float dt);
		void OnRuntimeUpdate(float dt);
		void OnRender();
		
		void SetEventCallback(const EventCallbackFn& callback);
		
		void SaveActiveScene();

		void SetActiveScene(const std::string path);	

		inline std::shared_ptr<Scene> GetActiveScene() const { return m_scenes.front(); }

		inline bool HasActiveScene() {return (m_scenes.size() > 0);}

		inline std::shared_ptr<SceneSerializer> GetSceneSerializer() {return m_sceneSerializer;}
	};
}
