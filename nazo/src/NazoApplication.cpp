#include <zpch.h>
#include "NazoApplication.h"

namespace Nazo
{
#define BIND_EVENT_FN(x) std::bind(&Nazo::NazoApplication::x, this, std::placeholders::_1)

	NazoApplication::NazoApplication(const ApplicationSpecs& settings)
		: Application(settings)
	{

		m_editorLayer = new EditorLayer(this);
		PushLayer(m_editorLayer);
		m_editorLayer->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_imGuiLayer = new ImGuiLayer(this);
		PushOverlay(m_imGuiLayer);
		m_imGuiLayer->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}
}