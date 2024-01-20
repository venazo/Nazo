#pragma once

#include <imgui.h>
#include <imgui_internal.h>
#include <Zewada.h>

#define COLUMNWIDTH 150.0f

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
		
		static void DrawVec2Control(const std::string& label, glm::vec2& value);
		static void DrawVec3Control(const std::string& label, glm::vec3& value);
		static void DragFloat(const std::string& label, float& value);
		static void DragInt(const std::string& label, int& value);
		static void ColorPicker4(const std::string& label, glm::vec4& value);
		static bool DrawButton(const std::string& label, const glm::vec4& color);
		static void TextInput(const std::string& label, std::string& value);
		static int ComponentHeader(const std::string& label);
		static bool ImageButtonWithName(const std::string& label, ImTextureID texid);
		static void TextureInput(const std::string& label, std::shared_ptr<Sprite>& sprite);
		static void ScriptInput(const std::string& label, NativeScript& nativeScript);
		static void Frame(const std::string& label, Animation::Frame& frame);
		static void Animation(const std::string& label, Zewada::Animation& animation);

		template<typename T>
		static void Vector(std::string label, std::string singleLabel, std::vector<T>& values, std::function<void(const std::string&, T&)> draw)
		{
			ImGui::PushID(label.c_str());

			ImGui::Columns(1);

			if(ImGui::CollapsingHeader(label.c_str()))
			{
				for(int i = 0; i < values.size(); i++)
				{
					draw(singleLabel + " " + std::to_string(i + 1), values[i]);
				}

				if(DrawButton("Add", glm::vec4(0.3f, 0.8f, 0.2f, 1.0f)))
				{
					values.push_back(T());
				}

				ImGui::SameLine();

				if(DrawButton("Remove", glm::vec4(0.7f, 0.2f, 0.3f, 1.0f)))
				{
					if(values.size() > 0)
					{
						values.pop_back();
					}
				}
			}

			ImGui::Columns(1);

			ImGui::PopID();
		}

		
		template<typename K, typename V>
		static void Unordered_map(const std::string& label, const std::string& first, const std::string& second, std::unordered_map<K, V>& values,
			std::function<void(const std::string&, K&)> drawKey, std::function<void(const std::string&, V&)> drawValue)
		{
			ImGui::PushID(label.c_str());

			ImGui::Columns(1);

			if(ImGui::CollapsingHeader(label.c_str()))
			{
				K toDelete;
				int i = 1;
				for(auto& pair : values)
				{
					std::string key = pair.first;
					drawKey(first + " " + std::to_string(i), key);
					if(key != pair.first)
					{
						values.erase(pair.first);
						values.insert({key, pair.second});
					}
					drawValue(second + " " + std::to_string(i), pair.second);
					
					if(DrawButton("Remove", glm::vec4(0.7f, 0.2f, 0.3f, 1.0f)))
					{
						toDelete = pair.first;
					}

					i++;
				}

				values.erase(toDelete);

				ImGui::Columns(1);

				if(DrawButton("Add", glm::vec4(0.3f, 0.8f, 0.2f, 1.0f)))
				{
					if(values.size() > 0)
					{
						values["new " + std::to_string(values.size())] = Zewada::Animation();
					}
					else
					{
						values["new"] = Zewada::Animation();
					}

				}
			}

			ImGui::Columns(1);

			ImGui::PopID();
		}

		static void SetWriting(bool value);
		static void SetAssetPool(std::shared_ptr<AssetPool> assetPool);

		inline static ZImGui& Get()
		{
			static ZImGui zImGui;
			return zImGui;
		}
	};
}