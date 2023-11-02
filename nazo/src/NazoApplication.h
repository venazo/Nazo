#pragma once

#include <Zewada.h>
#include "Layers/EditorLayer.h"
#include "layers/ImGuiLayer.h"

using namespace Zewada;

namespace Nazo {
	class NazoApplication : public Zewada::Application
	{
	private:
		EditorLayer* m_editorLayer;
		ImGuiLayer* m_imGuiLayer;
	public:
		NazoApplication(const ApplicationSpecs& settings);

		inline EditorLayer* GetEditorLayer() {return m_editorLayer;}
		inline ImGuiLayer* GetImGuiLayer(){return m_imGuiLayer;}
	};
}

