#pragma once

#include <glm/glm.hpp>
#include "Texture.h"
#include <array>

namespace Zewada {

	class Sprite
	{
	private:
		std::string m_textureToLoad;
		std::shared_ptr<Texture> m_texture;
		std::array<glm::vec2, 4> m_texCoords;
	public:
		Sprite();
		Sprite(std::shared_ptr<Texture> texture);
		Sprite(std::shared_ptr<Texture> texture, const std::array<glm::vec2, 4>& texCoords);
		Sprite(const std::string& textureToLoad);
		Sprite(const std::string& textureToLoad, const std::array<glm::vec2, 4>& texCoords);

		void LoadTexture(std::shared_ptr<AssetPool> assetPool);

		void GenTexCoords();
		void GenFontCoords();
		void SetTexCoords(const std::array<glm::vec2, 4>& uv);
		void SetTexture(std::shared_ptr<Texture> texture);
		void SetTextureToLoad(const std::string& textureToLoad);

		inline const std::shared_ptr<Texture> GetTexture() const { return m_texture; }
		inline const std::array<glm::vec2, 4>& GetUV() const { return m_texCoords; }
		inline const bool HasTextureToLoad() {return (m_textureToLoad != "");}
	};
}
