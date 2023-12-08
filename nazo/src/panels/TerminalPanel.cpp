#include "TerminalPanel.h"

namespace Nazo
{
    TerminalPanel::TerminalPanel(std::shared_ptr<Logger> logger)
    {
        m_logger = logger;
    }

    void TerminalPanel::ImGui()
    {
        ImGui::Begin("Terminal");

        //x scrolling
        if(ImGui::IsWindowFocused())
        {
            float edge = -(ImGui::GetStyle().WindowPadding.x);
            static float x = edge;
            if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_LeftArrow)))
                x -= ImGui::GetIO().DeltaTime * 1000.0f;
            if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_RightArrow)))
                x += ImGui::GetIO().DeltaTime * 1000.0f;
            if((float)(int)x >= edge)
            {
                ImGui::SetCursorPosX((float)(int)-x);
            }
            else
            {
                ImGui::SetCursorPosX((float)(int)-edge);
                x = edge;
            }
        }

        const std::string log = m_logger->GetLog(); 
        ImGui::Text(log.c_str());

        ImGui::End();
    }
}