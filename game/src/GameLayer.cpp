#include "GameLayer.h"

namespace Game
{
#define BIND_EVENT_FN(x) std::bind(&Game::GameLayer::x, this, std::placeholders::_1)

    GameLayer::GameLayer(Application* application)
		:Layer()
    {
		m_application = application;
    }

    void GameLayer::OnAttach()
    {
        m_application->GetSerializer()->DeserializeAssets(m_application->GetAssetPool());

		m_defaultShader = m_application->GetAssetPool()->GetShader("assets/shaders/Default_Editor.glsl");
		
		m_application->GetSceneManager()->OnStart();
    }

    void GameLayer::OnUpdate(float dt)
    {
		m_application->GetRenderer2D()->Clear();
		m_application->GetRenderer2D()->BindShader(m_defaultShader);
		
        GameObject maincamera = GameObject(m_application->GetSceneManager()->GetActiveScene()->GetCameraSystem()->GetMaincameraObject(), m_application->GetSceneManager()->GetActiveScene());
		if(maincamera.operator bool())
		{
			m_application->GetInput()->CalcWorldMousePosition(maincamera.GetComponent<Transform>(), 
				maincamera.GetComponent<Camera>());
		}
		else
		{
			m_application->GetInput()->CalcWorldMousePosition(Transform(), Camera());
		}

		m_application->GetSceneManager()->OnRuntimeUpdate(dt);
		m_application->GetSceneManager()->OnRender();
    }

    void GameLayer::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnResize));
    }

    bool GameLayer::OnResize(WindowResizeEvent& event)
	{
		m_application->GetSceneManager()->GetActiveScene()->OnResize(event);
		return false;
	}

    void GameLayer::SetEventCallback(const EventCallbackFn& callback)
	{
		m_callback = callback;
		m_application->GetSceneManager()->SetEventCallback(callback);
	}
}
