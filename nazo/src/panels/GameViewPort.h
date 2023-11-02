#pragma once

#include "../utils/ZImGui.h"
#include <imgui.h>
#include <Zewada.h>

using namespace Zewada;

namespace Nazo {
	using EventCallbackFn = std::function<void(Event&)>;
	class GameViewPort
	{
	private:
		std::string m_name;
		float m_width, m_height;
		ImVec2 m_windowSize;	
		bool m_autoResize;
		bool m_active = false;

		glm::vec4 m_translation;

		Framebuffer* m_framebuffer;

		EventCallbackFn m_callback;

		Application* m_application;
	
		const ImVec2 GetLargestSizeForViewPort();
		const ImVec2 GetCentredPositionForViewPort(ImVec2 aspectSize);
	public:
		GameViewPort() = default;	
		GameViewPort(Application* application, const std::string& name, bool autoResize);
		void Resize(float width, float height);

		void ImGui();

		void Bind();
		void UnBind();

		void SetEventCallback(const EventCallbackFn& callback);

		inline const glm::vec4& GetTranslation(){return m_translation;}
		inline const float GetWindowWidth() { return m_windowSize.x; }
		inline const float GetWindowHeight() { return m_windowSize.y; }
		inline Framebuffer* GetFramebuffer() { return m_framebuffer; }
		
		inline const bool IsHovering() const {return m_active;};
	};
}