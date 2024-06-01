#include "AssetPanel.h"
#include "../layers/ImGuiLayer.h"

namespace Nazo
{
    AssetPanel::AssetPanel(ImGuiLayer* imGuiLayer, std::shared_ptr<AssetPool> assetPool, std::shared_ptr<SceneManager> sceneManager)
    {
        m_normalPath = std::filesystem::path(std::filesystem::current_path());
        m_currentPath = m_normalPath;
        m_assetPool = assetPool;
        m_sceneManager = sceneManager;
        m_folderSprite = Sprite(m_assetPool->GetTexture("assets/nazo/textures/folderIcon.png"));
        m_sceneSprite = Sprite(m_assetPool->GetTexture("assets/nazo/textures/sceneIcon.png"));
        m_fileSprite = Sprite(m_assetPool->GetTexture("assets/nazo/textures/fileIcon.png"));
        m_prefabsSprite = Sprite(m_assetPool->GetTexture("assets/nazo/textures/prefabsIcon.png"));
        m_soundSprite = Sprite(m_assetPool->GetTexture("assets/nazo/textures/soundIcon.png"));
        m_imGuiLayer = imGuiLayer;
    }

    void AssetPanel::ImGui()
    {
        ImGui::Begin("AssetPanel");

        auto* window = ImGui::GetCurrentWindow();

        if(ImGui::BeginDragDropTargetCustom(window->ContentRegionRect, window->ID))
        {
            const ImGuiPayload* payLoadObj = ImGui::AcceptDragDropPayload(dragDropGameObject);
			if(payLoadObj != nullptr)
			{
				GameObject* go = (GameObject*)payLoadObj->Data;
                if(go->operator bool())
                {
                    m_sceneManager->GetSceneSerializer()->SerializePrefabs(*go, m_currentPath.string() + "/" + go->GetComponent<Tag>().name + ".zp");
                }
			}
            ImGui::EndDragDropTarget();
        }

        if(ImGui::Button("<-"))
        {
            m_currentPath = m_currentPath.parent_path();
        }

        float padding = ImGui::GetStyle().FramePadding.x;
		float cellSize = 128.0f + padding;
        float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
        if (columnCount < 1)
			columnCount = 1;

        ImGui::Columns(columnCount, 0, false);
        auto directory = std::filesystem::directory_iterator(m_currentPath);
        for (const auto & entry : directory)
        {
            std::filesystem::path path = entry.path();
            if(entry.is_directory())
            {
                FolderImGui(path);
            }
            else if(path.has_extension())
            {
                std::string filetype = path.extension().string();
                if(filetype == ".zs")
                {
                    SceneImGui(path);
                }
                else if(filetype == ".png" || filetype == ".jpg")
                {
                    TextureImGui(path);
                }
                else if(filetype == ".cpp" || filetype == ".h")
                {
                    ScriptImGui(path); 
                }
                else if(filetype == ".zp")
                {
                    PrefabsImGui(path);
                }
                else if(filetype == ".wave" || filetype == ".wav" || filetype == ".mp3")
                {
                    SoundImGui(path);
                }
                else
                {
                    FileImGui(path);
                }
            }
            else
                continue;
            ImGui::NextColumn();
        }

        ImGui::NewLine();
        ImGui::End();
    }

    void AssetPanel::FolderImGui(std::filesystem::path& path)
    {
        ImTextureID textureid = (ImTextureID)m_folderSprite.GetTexture()->GetID();
        std::string name = path.filename().string();
        ImGui::PushID(name.c_str());
		ImVec2 padding = ImGui::GetStyle().FramePadding;

		ImGui::BeginChild(name.c_str(), ImVec2(128.0f + (padding.x * 2.0f),
			128.0f + ImGui::GetFontSize() + (padding.y * 4.0f)));
		ImGui::ImageButton(textureid, {128, 128}, {0, 1}, {1, 0});
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			m_currentPath /= path.filename();
		}
        if(ImGui::BeginDragDropTarget())
	    {
			const ImGuiPayload* payLoadObj = ImGui::AcceptDragDropPayload(dragDropGameObject);
			if(payLoadObj != nullptr)
			{
				GameObject* go = (GameObject*)payLoadObj->Data;
                if(go->operator bool())
                {
                    std::string newPath = (m_currentPath / path.filename()).string();
                    m_sceneManager->GetSceneSerializer()->SerializePrefabs(*go, newPath + "/" + go->GetComponent<Tag>().name + ".zp");
                }
			}
            ImGui::EndDragDropTarget();
		}

        

		ImGui::Text(name.c_str());


        ImGui::EndChild();
		ImGui::PopID();
    }

    void AssetPanel::SceneImGui(std::filesystem::path& path)
    {
        ImTextureID textureid = (ImTextureID)m_sceneSprite.GetTexture()->GetID();
        std::string name = path.filename().string();
        ImGui::PushID(name.c_str());
		ImVec2 padding = ImGui::GetStyle().FramePadding;

		ImGui::BeginChild(name.c_str(), ImVec2(128.0f + (padding.x * 2.0f),
			128.0f + ImGui::GetFontSize() + (padding.y * 4.0f)));
		ImGui::ImageButton(textureid, {128, 128}, {0, 1}, {1, 0});
        if(ImGui::BeginDragDropSource())
        {
            std::filesystem::path relativePath = FileUtils::RelativePath(path);
			const wchar_t* itemPath = relativePath.c_str();
            ImGui::SetDragDropPayload(dragDropScene, itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
            ImGui::Text(name.c_str());
            ImGui::EndDragDropSource();
        }
		ImGui::Text(name.c_str());

        ImGui::EndChild();
		ImGui::PopID();
    }

    void AssetPanel::TextureImGui(std::filesystem::path& path)
    {
        std::string pathStr = path.string();
        if(!Utils::Contains(m_open, pathStr))
        {
            m_open.insert({pathStr, false});
        }

        auto tex = m_assetPool->GetTextureAbsolutePath(pathStr.c_str());
        ImTextureID textureid = (ImTextureID)tex->GetID();
        std::string name = path.filename().string();
        ImGui::PushID(name.c_str());
		ImVec2 padding = ImGui::GetStyle().FramePadding;

		ImGui::BeginChild(name.c_str(), ImVec2(128.0f + (padding.x * 2.0f),
			128.0f + ImGui::GetFontSize() + (padding.y * 4.0f)));
        
		if(ImGui::ImageButton(textureid, {128, 128}, {0, 1}, {1, 0}))
        {     
            m_open[pathStr] = !m_open[pathStr];
        }
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			m_imGuiLayer->GetPropertiesPanel()->SetTexture(tex);
		}
        std::filesystem::path relativePath = FileUtils::RelativePath(path);
        if(ImGui::BeginDragDropSource())
        {
			const wchar_t* itemPath = relativePath.c_str();
            ImGui::SetDragDropPayload(dragDropTexture, itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
            ImGui::Text(name.c_str());
            ImGui::EndDragDropSource();
        }
		ImGui::Text(name.c_str());

        ImGui::EndChild();
		ImGui::PopID();

        if(m_assetPool->ExistSpriteSheet(relativePath.string().c_str()) && m_open[pathStr])
        {
            DrawSprites(relativePath);
        }
    }

    void AssetPanel::FileImGui(std::filesystem::path& path)
    {
        ImTextureID textureid = (ImTextureID)m_fileSprite.GetTexture()->GetID();
        std::string name = path.filename().string();
        ImGui::PushID(name.c_str());
		ImVec2 padding = ImGui::GetStyle().FramePadding;

		ImGui::BeginChild(name.c_str(), ImVec2(128.0f + (padding.x * 2.0f),
			128.0f + ImGui::GetFontSize() + (padding.y * 4.0f)));
		ImGui::ImageButton(textureid, {128, 128}, {0, 1}, {1, 0});
		ImGui::Text(name.c_str());

        ImGui::EndChild();
		ImGui::PopID();
    }

    void AssetPanel::ScriptImGui(std::filesystem::path& path)
    {
        ImTextureID textureid = (ImTextureID)m_fileSprite.GetTexture()->GetID();
        std::string name = path.filename().string();
        ImGui::PushID(name.c_str());
		ImVec2 padding = ImGui::GetStyle().FramePadding;

		ImGui::BeginChild(name.c_str(), ImVec2(128.0f + (padding.x * 2.0f),
			128.0f + ImGui::GetFontSize() + (padding.y * 4.0f)));
		ImGui::ImageButton(textureid, {128, 128}, {0, 1}, {1, 0});
        std::filesystem::path relativePath = FileUtils::RelativePath(path);
        if(ImGui::BeginDragDropSource())
        {
            const wchar_t* itemPath = relativePath.c_str();
            ImGui::SetDragDropPayload(dragDropScript, itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
            ImGui::Text(name.c_str());
            ImGui::EndDragDropSource();
        }

		ImGui::Text(name.c_str());

        ImGui::EndChild();
		ImGui::PopID();
    }

    void AssetPanel::DrawSprites(std::filesystem::path& relativePath)
    {
        ImGui::NextColumn();
        auto sprites = m_assetPool->GetSpriteSheet(relativePath.string().c_str())->GetSprites();
        for(int i = 0; i < sprites.size(); i++)
        {
            auto tex = sprites[i]->GetTexture();
            ImTextureID textureid = (ImTextureID)tex->GetID();
            std::string name = relativePath.filename().string() + " "+ std::to_string(i + 1);
            ImGui::PushID(name.c_str());
		    ImVec2 padding = ImGui::GetStyle().FramePadding;

		    ImGui::BeginChild(name.c_str(), ImVec2(128.0f + (padding.x * 2.0f),
			    128.0f + ImGui::GetFontSize() + (padding.y * 4.0f)));

            auto UV = sprites[i]->GetUV();
		    ImGui::ImageButton(textureid, {128, 128}, {UV[1].x, UV[1].y}, {UV[3].x, UV[3].y});
            if(ImGui::BeginDragDropSource())
            {
                std::string sprite = relativePath.string() + "$.%.$" + std::to_string(i);
                std::wstring wsprite(sprite.begin(), sprite.end());
                const wchar_t* itemPath = wsprite.c_str();
                ImGui::SetDragDropPayload(dragDropSprite, itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
                ImGui::Text(name.c_str());
                ImGui::EndDragDropSource();
            }

            ImGui::EndChild();
		    ImGui::PopID();
            if(i < sprites.size() - 1.0f)
                ImGui::NextColumn();
        }
    }

    void AssetPanel::PrefabsImGui(std::filesystem::path& path)
    {
        ImTextureID textureid = (ImTextureID)m_prefabsSprite.GetTexture()->GetID();
        std::string name = path.filename().string();
        ImGui::PushID(name.c_str());
		ImVec2 padding = ImGui::GetStyle().FramePadding;

		ImGui::BeginChild(name.c_str(), ImVec2(128.0f + (padding.x * 2.0f),
			128.0f + ImGui::GetFontSize() + (padding.y * 4.0f)));
		ImGui::ImageButton(textureid, {128, 128}, {0, 1}, {1, 0});
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			m_sceneManager->GetSceneSerializer()->DeserializePrefabs(path.string(), m_sceneManager->GetActiveScene());
		}
        ImGui::Text(name.c_str());
        
        ImGui::EndChild();
		ImGui::PopID();
    }

    void AssetPanel::SoundImGui(std::filesystem::path& path)
    {
        ImTextureID textureid = (ImTextureID)m_soundSprite.GetTexture()->GetID();
        std::string name = path.filename().string();
        ImGui::PushID(name.c_str());
		ImVec2 padding = ImGui::GetStyle().FramePadding;

		ImGui::BeginChild(name.c_str(), ImVec2(128.0f + (padding.x * 2.0f),
			128.0f + ImGui::GetFontSize() + (padding.y * 4.0f)));
		ImGui::ImageButton(textureid, {128, 128}, {0, 1}, {1, 0});
        ImGui::Text(name.c_str());
        
        ImGui::EndChild();
		ImGui::PopID();
    }
}