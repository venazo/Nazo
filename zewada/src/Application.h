#pragma once

#include "graphics/Window.h"
#include "utils/Input.h"
#include "scene/SceneManager.h"
#include "graphics/openGL/DebugDrawing/DebugDraw.h"
#include "utils/resource/ScriptLoader.h"
#include "scene/SceneSerializer.h"

#include "../src/utils/Time.h"
#include "utils/debug/Logger.h"

#include "events/ApplicationEvent.h"
#include "layers/LayerStack.h"

#include <filesystem>

#ifdef _WIN

#else
#error only Windows support!
#endif

struct ApplicationSpecs
{
	std::string name = "Zewada Project";

	unsigned int width = 1600;
	unsigned int height = 900;

	bool vSync = false;
	bool resizeable = true;
};

namespace Zewada
{
	class Application
	{
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		void SetCallbacks();
	public:
		Application(const ApplicationSpecs& settings);
		~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline std::shared_ptr<Logger> GetLogger() const {return m_logger;}
		inline std::shared_ptr<Window> GetWindow() const { return m_window; }
		inline std::shared_ptr<Input> GetInput() const { return m_input; }
		inline std::shared_ptr<AssetPool> GetAssetPool() const {return m_assetPool;}
		inline std::shared_ptr<SceneManager> GetSceneManager() const { return m_sceneManager; }
		inline std::shared_ptr<Renderer2D> GetRenderer2D() const {return m_renderer2D;}
		inline std::shared_ptr<DebugDraw> GetDebugDraw() const { return m_debugDraw;}
		inline std::shared_ptr<Physics2D> GetPhysics2D() const {return m_physics2D;}
		inline std::shared_ptr<ScriptLoader> GetScriptLoader() const { return m_scriptLoader;}


		void Run();
	private:
		std::shared_ptr<Logger> m_logger;
		std::shared_ptr<Window> m_window;
		std::shared_ptr<Input> m_input;
		std::shared_ptr<AssetPool> m_assetPool;
		std::shared_ptr<SceneManager> m_sceneManager;
		std::shared_ptr<Renderer2D> m_renderer2D;
		std::shared_ptr<DebugDraw> m_debugDraw;
		std::shared_ptr<Physics2D> m_physics2D;
		std::shared_ptr<ScriptLoader> m_scriptLoader;



		const ApplicationSpecs& m_settings;

		bool m_running = true;
		bool m_minimized = false;

		LayerStack m_layerStack;

	};
}

