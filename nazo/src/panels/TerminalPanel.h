#pragma once

#include <Zewada.h>
#include <imgui.h>
#include "../utils/ZImGui.h"

using namespace Zewada;

namespace Nazo
{
    class TerminalPanel
    {
    private:
        std::shared_ptr<Logger> m_logger;
    public:
        TerminalPanel(std::shared_ptr<Logger> logger);

        void ImGui();
    };
}