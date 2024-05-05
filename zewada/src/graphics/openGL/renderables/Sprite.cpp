#include <zpch.h>
#include "Sprite.h"
#include "../../../utils/resource/AssetPool.h"

namespace Zewada {

	Sprite::Sprite()
	{
		m_texture = std::make_shared<Texture>();
		GenTexCoords();
	}
	
	Sprite::Sprite(std::shared_ptr<Texture> texture)
	{
		m_texture = texture;
		GenTexCoords();
		m_textureToLoad = "";
	}

	Sprite::Sprite(std::shared_ptr<Texture> texture, const std::array<glm::vec2, 4>& texCoords)
	{
		m_texture = texture;
		m_texCoords = texCoords;
		m_textureToLoad = "";
	}

	Sprite::Sprite(const std::string& textureToLoad)
	{
		m_textureToLoad = textureToLoad;
		GenTexCoords();
	}

	Sprite::Sprite(const std::string& textureToLoad, const std::array<glm::vec2, 4>& texCoords)
	{
		m_textureToLoad = textureToLoad;
		m_texCoords = texCoords;
	}

	void Sprite::LoadTexture(std::shared_ptr<AssetPool> assetPool)
	{
		SetTexture(assetPool->GetTexture(m_textureToLoad.c_str()));
	}

	void Sprite::SetTextureToLoad(const std::string& textureToLoad)
	{
		m_textureToLoad = textureToLoad;
	}

	void Sprite::GenTexCoords()
	{
		m_texCoords[0] = glm::vec2(0, 0);
		m_texCoords[1] = glm::vec2(0, 1);
		m_texCoords[2] = glm::vec2(1, 1);
		m_texCoords[3] = glm::vec2(1, 0);
	}

	void Sprite::SetTexCoords(const std::array<glm::vec2, 4>& uv)
	{
		m_texCoords = uv;
	}

	void Sprite::SetTexture(std::shared_ptr<Texture> texture)
	{
		m_texture = texture;
	}
}
