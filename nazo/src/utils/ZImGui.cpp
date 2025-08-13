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

	void Nazo::ZImGui::DrawVec2Control(const std::string& label, glm::vec2& value)
	{
		ImGui::PushID(label.c_str());
		
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, COLUMNWIDTH);
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
			value.x = 0.0f;
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
			value.y = 0.0f;
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

	void ZImGui::DrawVec3Control(const std::string& label, glm::vec3& value)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, COLUMNWIDTH);
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
			value.x = 0.0f;
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
			value.y = 0.0f;
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
			value.z = 0.0f;
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
	void ZImGui::DragFloat(const std::string& label, float& value)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, COLUMNWIDTH);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::DragFloat("##dragFloat", &value, 0.1f);

		ImGui::Columns(1);
		ImGui::PopID();
	}

	void ZImGui::DragInt(const std::string& label, int& value)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, COLUMNWIDTH);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::DragInt("##dragFloat", &value, 0.1f);

		ImGui::Columns(1);
		ImGui::PopID();
	}

	void ZImGui::ColorPicker4(const std::string& label, glm::vec4& value)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, COLUMNWIDTH);
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

	bool ZImGui::DrawButton(const std::string& label, const glm::vec4& color)
	{
		ImGui::PushID(label.c_str());

		float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;

		ImGui::Columns(1);

		ImGui::PushItemWidth(COLUMNWIDTH);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(color.x, color.y, color.z, color.w));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color.x + 0.1f, color.y + 0.1f, color.z + 0.1f, color.w));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color.x, color.y, color.z, color.w));
		bool result = ImGui::Button(label.c_str(), ImVec2(COLUMNWIDTH, lineHeight));
		
		ImGui::PopItemWidth();
		ImGui::PopStyleColor(3);
		ImGui::Columns(1);
		ImGui::PopID();

		return result;
	}
	
	void ZImGui::TextInput(const std::string& label, std::string& value)
	{	
		char value_c[32];
    	memcpy(value_c, value.c_str(), value.size() + 1);
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, COLUMNWIDTH);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushItemWidth(COLUMNWIDTH);
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

	int ZImGui::ComponentHeader(const std::string& label)
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
	
	bool ZImGui::ImageButtonWithName(const std::string& label, ImTextureID texid)
	{
		ImGui::PushID(label.c_str());
		ImVec2 padding = ImGui::GetStyle().FramePadding;

		ImGui::BeginChild(label.c_str(), ImVec2(128.0f + (padding.x * 2.0f),
			128.0f + ImGui::GetFontSize() + (padding.y * 4.0f)));
		bool result = ImGui::ImageButton("", texid, {128, 128}, {0, 1}, {1, 0});
		ImGui::Text(label.c_str());
		ImGui::EndChild();

		ImGui::PopID();
		return result;
	}
	
	void ZImGui::TextureInput(const std::string& label, std::shared_ptr<Sprite>& sprite)
	{
		ImGui::PushID(label.c_str());

		float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
		float width = ImGui::CalcItemWidth();

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, COLUMNWIDTH);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		const std::string path = sprite->GetTexture()->GetPath();				
		std::filesystem::path realPath(path);
		std::string name = realPath.filename().string();

		ImGui::PushItemWidth(COLUMNWIDTH);
		if(ImGui::Button(name.c_str()))
		{
			sprite->SetTexture(std::make_shared<Texture>());
		}

		if(ImGui::BeginDragDropTarget())
	    {
			const ImGuiPayload* payLoadObj = ImGui::AcceptDragDropPayload("Texture");
			const ImGuiPayload* payLoadSprite = ImGui::AcceptDragDropPayload("Sprite");
			if(payLoadObj != nullptr)
			{
				const wchar_t* path = (wchar_t*)payLoadObj->Data;
				std::filesystem::path scenePath(path);
				sprite = std::make_shared<Sprite>(Get().m_assetPool->GetTexture(scenePath.string().c_str()));
			}
			else if(payLoadSprite != nullptr)
			{
				const wchar_t* charSprite = (wchar_t*)payLoadSprite->Data;
				std::wstring wsprite(charSprite);
				std::string spritePath(wsprite.begin(), wsprite.end());
				unsigned int size = spritePath.find("$.%.$");
				std::string path = spritePath.substr(0, size);
				int num = std::stoi(spritePath.substr(size + 5, spritePath.length()));
				sprite = Get().m_assetPool->GetSpriteSheet(path.c_str())->GetSprite(num);
			}
		}
		ImGui::PopItemWidth();
		ImGui::Columns(1);

		ImGui::PopID();
	}	
	
	void ZImGui::ScriptInput(const std::string& label, NativeScript& nativeScript)
	{
		ImGui::PushID(label.c_str());

		float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
		float width = ImGui::CalcItemWidth();

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, COLUMNWIDTH);
		ImGui::Text("Script");
		ImGui::NextColumn();

		ImGui::PushItemWidth(COLUMNWIDTH);
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

	void ZImGui::Frame(const std::string& label, Animation::Frame& frame)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(1);

		ImGui::Text(label.c_str());

		TextureInput("Texture", frame.sprite);
		DragFloat("Duration", frame.duration);

		ImGui::Columns(1);

		ImGui::PopID();
	}

	void ZImGui::Animation(const std::string& label, Zewada::Animation& animation)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(1);

		Vector<Animation::Frame>(label.c_str(), "Frame", animation.frames, ZImGui::Frame);		

		ImGui::Columns(1);

		ImGui::PopID();
	}

	void ZImGui::Combo(const std::string& label, const std::vector<std::string>& values, std::string& activeObject)
	{
		ImGui::PushID(label.c_str());

		float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
		float width = ImGui::CalcItemWidth();

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, COLUMNWIDTH);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushItemWidth(COLUMNWIDTH);

		std::string result = activeObject;

		if(ImGui::BeginCombo("##Combo", activeObject.c_str()))
		{
			for(int i = 0; i < values.size(); i++)
			{
				bool is_selected = (activeObject == values[i]);
				if (ImGui::Selectable(values[i].c_str(), is_selected))
            		result = values[i];
        		if (is_selected)
            		ImGui::SetItemDefaultFocus(); 
			}
			ImGui::EndCombo();
		}

		ImGui::PopItemWidth();
		ImGui::Columns(1);

		ImGui::PopID();

		activeObject = result;
	}

	void ZImGui::SetAssetPool(std::shared_ptr<AssetPool> assetPool)
	{
		Get().m_assetPool = assetPool;
	}

	void ZImGui::FontInput(std::string& font)
	{
		ImGui::PushID(font.c_str());

		float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
		float width = ImGui::CalcItemWidth();

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, COLUMNWIDTH);
		ImGui::Text("Font");
		ImGui::NextColumn();

		ImGui::PushItemWidth(COLUMNWIDTH);
		if(ImGui::Button(font.c_str()))
		{
			font = "assets/fonts/OpenSans-Regular.TTF";
		}

		if(ImGui::BeginDragDropTarget())
	    {
			const ImGuiPayload* payLoadObj = ImGui::AcceptDragDropPayload("Font");
			if(payLoadObj != nullptr)
			{
				const wchar_t* path = (wchar_t*)payLoadObj->Data;
				std::filesystem::path fontPath(path);
				std::filesystem::path relativePath = FileUtils::RelativePath(fontPath);
				font = relativePath.string();
			}
		}
		ImGui::PopItemWidth();
		ImGui::Columns(1);

		ImGui::PopID();
	}

	void ZImGui::SetWriting(bool value)
	{
		Get().m_writing = value;
	}
}
