#include <zpch.h>
#include "Application.h"
#include <Zewada.h>

#define BIND_EVENT_FN(x) std::bind(&Zewada::Application::x, this, std::placeholders::_1)

namespace Zewada
{

	Application::Application(const ApplicationSpecs& settings)
		: m_settings(settings)
	{
		FileUtils::SetCurrentPath();

		m_logger = std::make_shared<Logger>();
		m_window = std::make_shared<Window>(m_settings.name.c_str(), settings.width, settings.height, settings.vSync, settings.resizeable);
		m_input = std::make_shared<Input>(this);
		m_assetPool = std::make_shared<AssetPool>();
		m_sceneManager = std::make_shared<SceneManager>(this);
		m_sceneSerializer = m_sceneManager->GetSceneSerializer();
		m_renderer2D = std::make_shared<Renderer2D>();
		m_debugDraw = std::make_shared<DebugDraw>(m_assetPool->GetShader("assets/shaders/Debug2DLines.glsl"));
		m_physics2D = std::make_shared<Physics2D>(m_sceneManager);
		m_scriptLoader = std::make_shared<ScriptLoader>();

		m_window->SetIcon("assets/textures/test.png");

		m_sceneManager->CreateDefaultScene();

		SetCallbacks();
	}

	void Application::SetCallbacks()
	{
		m_window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_sceneManager->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
		m_assetPool->DeleteSounds();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
		m_input->OnEvent(e);

		for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_layerStack.PushOverlay(layer);
		layer->OnAttach();
	}

    bool Application::OnKeyPressed(KeyPressedEvent &e)
    {
		if(e.GetKeyCode() == GLFW_KEY_F11)
		{
			if(m_window->IsFullscreen())
				m_window->SetFullscreen(false);
			else
				m_window->SetFullscreen(true);
		}
        return false;
    }

    bool Application::OnWindowClose(WindowCloseEvent &e)
    {
		m_running = false;
		m_sceneManager->OnStop();
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_minimized = true;
			return false;
		}

		m_minimized = false;
		return false;
	}

	void Application::Run()
	{
		Time time;
		time.StartTime();
		float beginTime = time.GetTime();
		float endTime = time.GetTime();
		float dt = -1.0f;
		while (m_running)
		{
			m_window->OnClear();
			m_input->CalcAbsoluteMousePosition();
			if (!m_minimized)
			{
				for (Layer* layer : m_layerStack)
				{
					layer->OnUpdate(dt);
				}
			}

			m_window->OnUpdate();

			endTime = time.GetTime();
			dt = endTime - beginTime;
			beginTime = endTime;
		}

		m_sceneSerializer->IsBusy();
	}
}