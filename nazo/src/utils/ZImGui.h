#pragma once

#include <imgui.h>
#include <imgui_internal.h>
#include <Zewada.h>

using namespace Zewada;

namespace Nazo {
	class ZImGui
	{
	private:
		bool m_writing = false;
		std::shared_ptr<AssetPool> m_assetPool;
	public:
		void OnEvent(Event& event);
		bool OnKeyPressed(KeyPressedEvent& event);
		
		static void DrawVec2Control(std::string label, glm::vec2& value, float resetValue = 0.0f, float columnWidth = 150.0f);
		static void DrawVec3Control(std::string label, glm::vec3& value, float resetValue = 0.0f, float columnWidth = 150.0f);
		static void DragFloat(std::string label, float& value, float resetValue = 0.0f, float columnWidth = 150.0f);
		static void DragInt(std::string label, int& value, float resetValue = 0.0f, float columnWidth = 150.0f);
		static void ColorPicker4(std::string label, glm::vec4& value, float resetValue = 0.0f, float columnWidth = 150.0f);
		static bool DrawButton(std::string label, const glm::vec4& color, float columnWidth = 150.0f);
		static void TextInput(std::string label, std::string& value, float columnWidth = 150.0f);
		static int ComponentHeader(std::string label, float columnWidth = 300.0f);
		static bool ImageButtonWithName(std::string label, ImTextureID texid);
		static void TextureInput(std::string label, SpriteRenderer& spriteRenderer, float columnWidth = 150.0f);
		static void ScriptInput(std::string label, NativeScript& nativeScript, float columnWidth = 150.0f);

		static void SetWriting(bool value);
		static void SetAssetPool(std::shared_ptr<AssetPool> assetPool);

		inline static ZImGui& Get()
		{
			static ZImGui zImGui;
			return zImGui;
		}
	};
}