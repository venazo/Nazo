#pragma once

#include "../Utils/ZImGui.h"
#include <Zewada.h>
#include <memory>

using namespace Zewada;

namespace Nazo {

	class NazoApplication;

	class PropertiesPanel
	{
	private:
		std::shared_ptr<GameObject> m_activeGameObject;
		std::shared_ptr<Texture> m_activeTexture;

		NazoApplication* m_application;
	public:
		PropertiesPanel(NazoApplication* application);

		void SpriteEditor();
		void SpriteSheetEditor();
		void SetTexture(std::shared_ptr<Texture> tex);
		void ImGui();
	};
}