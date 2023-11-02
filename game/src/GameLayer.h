#pragma once

#include <math.h>
#include <Zewada.h>
#include <memory>

using namespace Zewada;

namespace Game {
	using EventCallbackFn = std::function<void(Event&)>;
	class GameLayer : public Layer
	{
	private:
		std::shared_ptr<Shader> m_defaultShader;

		EventCallbackFn m_callback;

		Application* m_application;
	public:
		GameLayer(Application* application);

		void OnAttach();
		void OnUpdate(float dt);
        void OnEvent(Event& event);
        bool OnResize(WindowResizeEvent& event);
		
		void SetEventCallback(const EventCallbackFn& callback);
	};
}