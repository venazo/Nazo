#pragma once

#include <math.h>
#include <Zewada.h>
#include "../Panels/GameViewPort.h"
#include "../Controls/CameraController.h"
#include "../Controls/Gizmos/GizmoSystem.h"
#include <memory>

using namespace Zewada;

namespace Nazo {
	
	class NazoApplication;

	using EventCallbackFn = std::function<void(Event&)>;
	class EditorLayer : public Layer
	{
	private:
		NazoApplication* m_application;

		std::shared_ptr<Shader> m_defaultShader;

		EventCallbackFn m_callback;
		
		bool m_loading;
		bool m_scenePlaying;
		std::unique_ptr<CameraController> m_cameraController;
		std::unique_ptr<GizmoSystem> m_gizmoSystem;

		std::shared_ptr<GameObject> m_activeGameObject;
		int m_activeID = -1;

		unsigned int m_frames = 0;
		float m_passed = 0.0f;

		bool m_ctr, m_shift;	

		bool m_gridActive = false;

		bool CheckActiveGameObject();
		void EditorDrawing();
	public:
		EditorLayer(NazoApplication* application);

		void OnEvent(Event& event);
		bool OnResize(WindowResizeEvent& event);
		bool OnKeyPressed(KeyPressedEvent& event);
		bool OnKeyReleased(KeyReleasedEvent& event);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& event);
		bool OnGameStart(GameStartEvent& event);
		bool OnGameEnd(GameEndEvent& event);
		bool OnLoadScene(LoadSceneEvent& event);
		bool OnSaveScene(SaveSceneEvent& event);
		bool OnChangedScene(ChangedSceneEvent& event);

		void OnAttach();
		void OnUpdate(float dt);

		inline std::shared_ptr<GameObject> GetActiveGameObject() {return m_activeGameObject;};
		bool SetGameObject(Entity id);
		
		void SetEventCallback(const EventCallbackFn& callback);

		inline bool IsPlaying() {return m_scenePlaying;}
	};
}