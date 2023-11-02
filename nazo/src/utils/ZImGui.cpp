#include <zpch.h>
#include "ZImGui.h"

namespace Nazo
{

#define BIND_EVENT_FN(x) std::bind(&Nazo::ZImGui::x, this, std::placeholders::_1)
	
	void ZImGui::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
	}

	bool ZImGui::OnKeyPressed(KeyPressedEvent& event)
	{
		if(m_writing)
		{
			return true;
		}
		return false;
	}

	void Nazo::ZImGui::DrawVec2Control(std::string label, glm::vec2& value, float resetValue, float columnWidth)
	{
		ImGui::PushID(label.c_str());
		
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2());

		float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
		ImVec2 buttonSize = ImVec2(lineHeight + 3.0f, lineHeight);
		float widthEach = (ImGui::CalcItemWidth() - buttonSize.x * 2.0f) / 2.0f;

		ImGui::PushItemWidth(widthEach);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		if (ImGui::Button("X", buttonSize))
		{
			value.x = resetValue;
		}
		
		ImGui::SameLine();
		ImGui::DragFloat("##x", &value.x, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PopStyleColor(3);

		ImGui::PushItemWidth(widthEach);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		if (ImGui::Button("Y", buttonSize))
		{
			value.y = resetValue;
		}

		ImGui::SameLine();
		ImGui::DragFloat("##y", &value.y, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PopStyleColor(3);


		ImGui::NextColumn();

		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::PopID();
	}

	void ZImGui::DrawVec3Control(std::string label, glm::vec3& value, float resetValue, float columnWidth)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2());

		float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
		ImVec2 buttonSize = ImVec2(lineHeight + 3.0f, lineHeight);
		float widthEach = (ImGui::CalcItemWidth() - buttonSize.x * 3.0f) / 3.0f;

		ImGui::PushItemWidth(widthEach);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		if (ImGui::Button("X", buttonSize))
		{
			value.x = resetValue;
		}
		
		ImGui::SameLine();
		ImGui::DragFloat("##x", &value.x, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PopStyleColor(3);

		ImGui::PushItemWidth(widthEach);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		if (ImGui::Button("Y", buttonSize))
		{
			value.y = resetValue;
		}

		ImGui::SameLine();
		ImGui::DragFloat("##y", &value.y, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PopStyleColor(3);

		ImGui::PushItemWidth(widthEach);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.15f, 0.8f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.2f, 0.9f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.15f, 0.8f, 1.0f));
		if (ImGui::Button("Z", buttonSize))
		{
			value.z = resetValue;
		}

		ImGui::SameLine();
		ImGui::DragFloat("##z", &value.z, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PopStyleColor(3);

		ImGui::NextColumn();

		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::PopID();
	}
	void ZImGui::DragFloat(std::string label, float& value, float resetValue, float columnWidth)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::DragFloat("##dragFloat", &value, 0.1f);

		ImGui::Columns(1);
		ImGui::PopID();
	}

	void ZImGui::DragInt(std::string label, int& value, float resetValue, float columnWidth)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::DragInt("##dragFloat", &value, 0.1f);

		ImGui::Columns(1);
		ImGui::PopID();
	}

	void ZImGui::ColorPicker4(std::string label, glm::vec4& value, float resetValue, float columnWidth)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		float color[] = { value.x, value.y, value.z, value.w };
		if (ImGui::ColorEdit4("##Color Picker", color))
		{
			value.x = color[0];
			value.y = color[1];
			value.z = color[2];
			value.w = color[3];
		}

		ImGui::Columns(1);
		ImGui::PopID();
	}

	bool ZImGui::DrawButton(std::string label, const glm::vec4& color, float columnWidth)
	{
		ImGui::PushID(label.c_str());

		float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;

		ImGui::Columns(1);
		ImGui::SetColumnWidth(0, columnWidth);

		ImGui::PushItemWidth(columnWidth);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(color.x, color.y, color.z, color.w));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color.x + 0.1f, color.y + 0.1f, color.z + 0.1f, color.w));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color.x, color.y, color.z, color.w));
		bool result = ImGui::Button(label.c_str(), ImVec2(columnWidth, lineHeight));
		
		ImGui::PopItemWidth();
		ImGui::PopStyleColor(3);
		ImGui::Columns(1);
		ImGui::PopID();

		return result;
	}
	
	void ZImGui::TextInput(std::string label, std::string& value, float columnWidth)
	{	
		char value_c[32];
    	memcpy(value_c, value.c_str(), value.size() + 1);
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushItemWidth(columnWidth);
		ImGui::InputText("##Text", value_c, 32);
		if(ImGui::IsItemFocused() && ImGui::IsItemClicked() && ImGui::IsItemActive())
		{
			Get().m_writing = true;
		}
		if(ImGui::IsItemDeactivatedAfterEdit())
		{
			Get().m_writing = false;
		}
		ImGui::PopItemWidth();
		ImGui::Columns(1);

		ImGui::PopID();

		value = std::string(value_c);
	}

	int ZImGui::ComponentHeader(std::string label, float columnWidth)
	{
		int result = 0;

		ImGui::PushID(label.c_str());

		float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
		float width = ImGui::CalcItemWidth();

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, width);
		if(ImGui::CollapsingHeader(label.c_str()))
		{
			result = 1;
		}
		ImGui::NextColumn();
		ImGui::PushItemWidth(30.0f);

		if(ImGui::Button("Del", ImVec2(30.0f, lineHeight)))
		{
			result = 2;
		}
		ImGui::PopItemWidth();
		ImGui::Columns(1);
		ImGui::PopID();
		return result;
	}
	
	bool ZImGui::ImageButtonWithName(std::string label, ImTextureID texid)
	{
		ImGui::PushID(label.c_str());
		ImVec2 padding = ImGui::GetStyle().FramePadding;

		ImGui::BeginChild(label.c_str(), ImVec2(128.0f + (padding.x * 2.0f),
			128.0f + ImGui::GetFontSize() + (padding.y * 4.0f)));
		bool result = ImGui::ImageButton(texid, {128, 128}, {0, 1}, {1, 0});
		ImGui::Text(label.c_str());
		ImGui::EndChild();

		ImGui::PopID();
		return result;
	}
	
	void ZImGui::TextureInput(std::string label, SpriteRenderer& spriteRenderer, float columnWidth)
	{
		ImGui::PushID(label.c_str());

		float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
		float width = ImGui::CalcItemWidth();

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text("Texture");
		ImGui::NextColumn();

		ImGui::PushItemWidth(columnWidth);
		if(ImGui::Button(label.c_str()))
		{
			spriteRenderer.sprite->SetTexture(std::make_shared<Texture>());
		}

		if(ImGui::BeginDragDropTarget())
	    {
			const ImGuiPayload* payLoadObj = ImGui::AcceptDragDropPayload("Texture");
			const ImGuiPayload* payLoadSprite = ImGui::AcceptDragDropPayload("Sprite");
			if(payLoadObj != nullptr)
			{
				const wchar_t* path = (wchar_t*)payLoadObj->Data;
				std::filesystem::path scenePath(path);
				spriteRenderer.sprite->SetTexture(Get().m_assetPool->GetTexture(scenePath.string().c_str()));
			}
			else if(payLoadSprite != nullptr)
			{
				const wchar_t* charSprite = (wchar_t*)payLoadSprite->Data;
				std::wstring wsprite(charSprite);
				std::string sprite(wsprite.begin(), wsprite.end());
				unsigned int size = sprite.find("$.%.$");
				std::string path = sprite.substr(0, size);
				int num = std::stoi(sprite.substr(size + 5, sprite.length()));
				spriteRenderer.sprite = Get().m_assetPool->GetSpriteSheet(path.c_str())->GetSprite(num);
			}
		}
		ImGui::PopItemWidth();
		ImGui::Columns(1);

		ImGui::PopID();
	}	
	
	void ZImGui::ScriptInput(std::string label, NativeScript& nativeScript, float columnWidth)
	{
		ImGui::PushID(label.c_str());

		float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
		float width = ImGui::CalcItemWidth();

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text("Script");
		ImGui::NextColumn();

		ImGui::PushItemWidth(columnWidth);
		if(ImGui::Button(label.c_str()))
		{
			nativeScript.className = "NONE";
		}

		if(ImGui::BeginDragDropTarget())
	    {
			const ImGuiPayload* payLoadObj = ImGui::AcceptDragDropPayload("Script");
			if(payLoadObj != nullptr)
			{
				const wchar_t* path = (wchar_t*)payLoadObj->Data;
				std::filesystem::path scenePath(path);
				std::string filename = scenePath.filename().string();
				std::string extension = scenePath.extension().string();
				int index = filename.find(extension);
				filename.erase(index, filename.length());
				nativeScript.className = filename;
			}
		}
		ImGui::PopItemWidth();
		ImGui::Columns(1);

		ImGui::PopID();
	}
	
	void ZImGui::SetAssetPool(std::shared_ptr<AssetPool> assetPool)
	{
		Get().m_assetPool = assetPool;
	}

	void ZImGui::SetWriting(bool value)
	{
		Get().m_writing = value;
	}
}
