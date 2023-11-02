#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "../Panels/GameViewPort.h"
#include "../panels/PropertiesPanel.h"
#include "../panels/SceneHierarchyPanel.h"
#include "../panels/AssetPanel.h"
#include "../panels/TerminalPanel.h"

#include <Layers/Layer.h>
#include <Application.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Nazo {
	class NazoApplication;
	using EventCallbackFn = std::function<void(Event&)>;
	class ImGuiLayer : public Zewada::Layer
	{
	private:
		NazoApplication* m_application;
		std::string m_filename;

		EventCallbackFn m_eventCallback;
		unsigned int m_width, m_height;

		bool m_isPlaying;

		GameViewPort m_editorView;
		GameViewPort m_gameView;
		PropertiesPanel m_propertiesPanel;
		SceneHierarchyPanel m_sceneHierarchyPanel;
		AssetPanel m_assetPanel;
		TerminalPanel m_terminalPanel;
	public:
		ImGuiLayer(NazoApplication* application);
		~ImGuiLayer();
		void OnAttach();
		void Start();
		void SetupDockSpace();
		void OnUpdate(float dt) override;
		void End();
		void OnEvent(Event& event);
		bool OnWindowResize(WindowResizeEvent& e);

		void SetEventCallback(const EventCallbackFn& callback);

		void SetDarkThemeColors();

		inline GameViewPort* GetEditorView() { return &m_editorView; }
		inline GameViewPort* GetGameView() { return &m_gameView; }
		inline PropertiesPanel* GetPropertiesPanel() {return &m_propertiesPanel;}
	};
}