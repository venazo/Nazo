#include <zpch.h>
#include "AssetPool.h"

namespace Zewada {

	std::shared_ptr<Shader> AssetPool::GetShader(const char* source)
	{
		std::filesystem::path pathstr(std::filesystem::current_path().string() + "/" + source);
		if(Utils::Contains(m_shaders, pathstr))
		{
			return m_shaders[pathstr];
		}

		//memeory of shader.m_path is dead lol
		std::shared_ptr<Shader> shader = std::make_shared<Shader>(pathstr.string().c_str());
		m_shaders.insert({ pathstr, shader });
		return shader;
	}

	std::shared_ptr<Texture> AssetPool::GetTexture(const char* source)
	{
		std::filesystem::path pathstr(std::filesystem::current_path().string() + "/" + source);

		if (Utils::Contains(m_textures, pathstr))
		{
			return m_textures[pathstr];
		}

		std::shared_ptr<Texture> texture = std::make_shared<Texture>(pathstr.string());
		m_textures.insert({ pathstr , texture });
		return texture;
	}

	std::shared_ptr<Texture> AssetPool::GetTextureAbsolutePath(const char* source)
	{
		std::filesystem::path pathstr(source);
		if (Utils::Contains(m_textures, pathstr))
		{
			return m_textures[pathstr];
		}

		std::shared_ptr<Texture> texture = std::make_shared<Texture>(pathstr.string());
		m_textures.insert({ pathstr, texture });
		return texture;
	}

	void AssetPool::AddSpriteSheet(std::shared_ptr<SpriteSheet> spriteSheet)
	{
		std::filesystem::path pathstr(spriteSheet->GetTexture()->GetPath());
		if (Utils::Contains(m_spriteSheets, pathstr))
		{
			Z_WARN("The SpriteSheet " + pathstr.string() + " has already been added!");
			return;
		}
		m_spriteSheets.insert({ pathstr, spriteSheet });
	}

	std::shared_ptr<SpriteSheet> AssetPool::GetSpriteSheet(const char* source)
	{
		std::filesystem::path pathstr(std::filesystem::current_path().string() + "/" + source);
		if (Utils::Contains(m_spriteSheets, pathstr))
		{
			return m_spriteSheets[pathstr];
		}
		Z_ERROR("The SpriteSheet " + pathstr.string() + " has not been added!");
		return std::make_shared<SpriteSheet>();
	}

	bool AssetPool::ExistSpriteSheet(const char* source)
	{
		std::filesystem::path pathstr(std::filesystem::current_path().string() + "/" + source);
		if (Utils::Contains(m_spriteSheets, pathstr))
		{
			return true;
		}
		return false;
	}	

	void AssetPool::DeleteSpriteSheet(const char* source)
	{
		std::filesystem::path pathstr(std::filesystem::current_path().string() + "/" + source);
		if (Utils::Contains(m_spriteSheets, pathstr))
		{
			m_spriteSheets.erase(pathstr);
			return;
		}
		Z_WARN("The SpriteSheet " + pathstr.string() + " has not been found!");
	}

	void AssetPool::ReplaceSpriteSheet(std::shared_ptr<SpriteSheet> spriteSheet)
	{
		std::filesystem::path pathstr(spriteSheet->GetTexture()->GetPath());
		if (Utils::Contains(m_spriteSheets, pathstr))
		{
			m_spriteSheets[pathstr] = spriteSheet;
			return;
		}
		Z_WARN("The SpriteSheet " + pathstr.string() + " has not been found!");
	}

	AssetPool::AssetPool()
	{
		GetShader("assets/shaders/Default_Editor.glsl");
		GetTexture("assets/nazo/textures/folderIcon.png");
		GetTexture("assets/nazo/textures/sceneIcon.png");
		GetTexture("assets/nazo/textures/fileIcon.png");
		AddSpriteSheet(std::make_shared<SpriteSheet>(GetTexture("assets/nazo/textures/gizmos.png"), 24, 48, 3, 0));
	}
}
