#pragma once

#include <filesystem>
#include "../Utils/ZImGui.h"
#include <Zewada.h>
#include <memory>

using namespace Zewada;

namespace Nazo
{
    class ImGuiLayer;

    class AssetPanel
    {
    private:
        std::filesystem::path m_currentPath;
        std::filesystem::path m_normalPath;

        Sprite m_folderSprite;
        Sprite m_sceneSprite;
        Sprite m_fileSprite;

        std::unordered_map<std::string, bool> m_open;

        const char* dragDropScene = "Scene";
        const char* dragDropTexture = "Texture";
        const char* dragDropSprite = "Sprite";
        const char* dragDropScript = "Script";

        ImGuiLayer* m_imGuiLayer;
        std::shared_ptr<AssetPool> m_assetPool;

        void DrawSprites(std::filesystem::path& relativePath);
    public:
        AssetPanel(ImGuiLayer* imGuiLayer, std::shared_ptr<AssetPool> assetPool);
        void ImGui();

        void FolderImGui(std::filesystem::path& path);
        void SceneImGui(std::filesystem::path& path);
        void TextureImGui(std::filesystem::path& path);
        void FileImGui(std::filesystem::path& path);
        void ScriptImGui(std::filesystem::path& path);
    };
}