#pragma once

#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <memory>
#include "../../Graphics/OpenGL/Renderables/Texture.h"
#include "../../Graphics/OpenGL/Renderer/Shader.h"
#include "../Debug/Logger.h"
#include "../../Graphics/OpenGL/Renderables/SpriteSheet.h"
#include "../Utils.h"
#include "Sound.h"

namespace Zewada {
	class AssetPool
	{
	private:
		std::map<std::filesystem::path, std::shared_ptr<Shader>> m_shaders;
		std::map<std::filesystem::path, std::shared_ptr<Texture>> m_textures;
		std::map<std::filesystem::path, std::shared_ptr<SpriteSheet>> m_spriteSheets;
		std::map<std::filesystem::path, std::shared_ptr<Zewada::Sound>> m_sounds;
		std::map<std::string, std::vector<std::shared_ptr<Zewada::Sprite>>> m_gridGroups;
	public:
		std::shared_ptr<Shader> GetShader(const char* source);
		std::shared_ptr<Texture> GetTexture(const char* source);
		std::shared_ptr<Texture> GetTextureAbsolutePath(const char* source);

		void AddSound(std::shared_ptr<Sound> sound);
		std::shared_ptr<Sound> GetSound(const char* source);

		bool ExistSpriteSheet(const char* source);
		void DeleteSpriteSheet(const char* source);
		void ReplaceSpriteSheet(std::shared_ptr<SpriteSheet> spriteSheet);
		void AddSpriteSheet(std::shared_ptr<SpriteSheet> spriteSheet);
		std::shared_ptr<SpriteSheet> GetSpriteSheet(const char* source);
		const std::map<std::filesystem::path, std::shared_ptr<SpriteSheet>>& GetAllSpriteSheets() {return m_spriteSheets; }

		std::map<std::string, std::vector<std::shared_ptr<Sprite>>>& GetGridGroups() 
		{
			return m_gridGroups;
		}

		void DeleteSounds();
		AssetPool();
	};

}