#include <zpch.h>
#include "GameViewPort.h"

namespace Nazo {
	GameViewPort::GameViewPort(Application* application, const std::string& name, bool autoResize)
	{
		m_name = name;
		m_application = application;
		m_width = m_application->GetWindow()->GetWidth();
		m_height = m_application->GetWindow()->GetHeight();
		m_application = application;
		m_windowSize = ImVec2(m_width, m_height);
		m_framebuffer = new Framebuffer(m_width, m_height);
		m_autoResize = autoResize;
	}

	void GameViewPort::ImGui()
	{
		ImGui::Begin(m_name.c_str(), 0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		
		ImVec2 windowSize = GetLargestSizeForViewPort();

		if(m_autoResize)
		{
			if (m_windowSize.x != windowSize.x || m_windowSize.y != windowSize.y)
			{
				m_windowSize = windowSize;
				//resize Everything acording new windowsize of GameViewPort
				WindowResizeEvent event(m_application->GetWindow()->GetWidth(), 
					m_application->GetWindow()->GetHeight());
				m_application->OnEvent(event);
			}
		}
		else
		{
			if(m_height / m_width * windowSize.x < windowSize.y )
			{
				m_windowSize.y = m_height / m_width * windowSize.x;
				m_windowSize.x = windowSize.x;
			}
			else
			{
				m_windowSize.x = m_width / m_height * windowSize.y;
				m_windowSize.y = windowSize.y;
			}
		}

		ImVec2 windowPos = GetCentredPositionForViewPort(m_windowSize);
		ImGui::SetCursorPos(windowPos);

		m_active = ImGui::IsWindowHovered();

		if(ImGui::IsWindowFocused())
		{
			ZImGui::SetWriting(false);
		}

		ImVec2 pos = ImGui::GetCursorScreenPos();
		pos.x -= ImGui::GetScrollX();
		pos.y -= ImGui::GetScrollY();

		m_translation = glm::vec4(pos.x, pos.y, m_windowSize.x, m_windowSize.y);
		ImTextureID textureid = (ImTextureID)m_framebuffer->GetTID();
		ImGui::Image(textureid, m_windowSize, ImVec2(0, 1), ImVec2(1, 0));
		if(ImGui::BeginDragDropTarget())
	    {
			const ImGuiPayload* payLoadObj = ImGui::AcceptDragDropPayload("Scene");
			if(payLoadObj != nullptr)
			{
				const wchar_t* path = (wchar_t*)payLoadObj->Data;
				std::filesystem::path scenePath(path);
				LoadSceneEvent event(scenePath.string());
				m_callback(event);
			}
			ImGui::EndDragDropTarget();
		}

		ImGui::End();
	}

	const ImVec2 GameViewPort::GetCentredPositionForViewPort(ImVec2 aspectSize)
	{
		ImVec2 windowSize;
		windowSize = ImGui::GetContentRegionAvail();
		windowSize.x -= ImGui::GetScrollX();
		windowSize.y -= ImGui::GetScrollY();

		float viewportX = (windowSize.x / 2.0f) - (aspectSize.x / 2.0f);
		float viewportY = (windowSize.y / 2.0f) - (aspectSize.y / 2.0f);

		return ImVec2(viewportX + ImGui::GetCursorPosX(), viewportY + ImGui::GetCursorPosY());
	}

	const ImVec2 GameViewPort::GetLargestSizeForViewPort()
	{
		ImVec2 windowSize;
		windowSize = ImGui::GetContentRegionAvail();
		windowSize.x -= ImGui::GetScrollX();
		windowSize.y -= ImGui::GetScrollY();

		return windowSize;
	}

	void GameViewPort::Resize(float width, float height)
	{
		m_framebuffer->Resize(width, height);
		m_width = width;
		m_height = height;
	}

	void GameViewPort::Bind()
	{
		m_application->GetInput()->SetTranslation(m_translation);
		m_application->GetInput()->CalcMousePosition();
		m_framebuffer->Bind();
		m_framebuffer->Clear();
	}

	void GameViewPort::UnBind()
	{
		m_application->GetInput()->SetTranslation(glm::vec4());
		m_framebuffer->UnBind();
	}

	void GameViewPort::SetEventCallback(const EventCallbackFn& callback)
	{
		m_callback = callback;
	}
}