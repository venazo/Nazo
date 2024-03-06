#include <zpch.h>
#include "NazoApplication.h"

namespace Nazo
{
#define BIND_EVENT_FN(x) std::bind(&Nazo::NazoApplication::x, this, std::placeholders::_1)

	NazoApplication::NazoApplication(const ApplicationSpecs& settings)
		: Application(settings)
	{
		GetAssetPool()->GetTexture("assets/nazo/textures/folderIcon.png");
		GetAssetPool()->GetTexture("assets/nazo/textures/sceneIcon.png");
		GetAssetPool()->GetTexture("assets/nazo/textures/prefabsIcon.png");
		GetAssetPool()->GetTexture("assets/nazo/textures/plusIcon.png");
		GetAssetPool()->AddSpriteSheet(std::make_shared<SpriteSheet>(GetAssetPool()->GetTexture("assets/nazo/textures/gizmos.png"), 24, 48, 3, 0));
		
		m_editorLayer = new EditorLayer(this);
		PushLayer(m_editorLayer);
		m_editorLayer->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_imGuiLayer = new ImGuiLayer(this);
		PushOverlay(m_imGuiLayer);
		m_imGuiLayer->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	NazoApplication::~NazoApplication()
	{
		GetSceneSerializer()->SerializeAssets(GetAssetPool());
	}
}