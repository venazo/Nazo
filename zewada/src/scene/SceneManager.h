#pragma once

#include "../Utils/Debug/Logger.h"
#include <vector>
#include <mutex>
#include <future>
#include <queue>

namespace Zewada {

	class Scene;
	class Event;
	class Application;

	using EventCallbackFn = std::function<void(Event&)>;

	class SceneManager : public std::enable_shared_from_this<SceneManager>
	{
	private:
		std::queue<std::shared_ptr<Scene>> m_scenes;
		EventCallbackFn m_callback;

		Application* m_application;
	public:
		SceneManager(Application* application);

		void CreateDefaultScene();
			
		void OnStart();
		void OnStop();
		void OnUpdate(float dt);
		void OnRuntimeUpdate(float dt);
		void OnRender();
		
		void SetEventCallback(const EventCallbackFn& callback);
		
		void SetActiveScene(const std::string path);
		inline std::shared_ptr<Scene> GetActiveScene() const { return m_scenes.front(); }
	};
}
