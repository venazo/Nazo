#pragma once

#include <glm/glm.hpp>
#include "Texture.h"
#include <array>

namespace Zewada {

	class Sprite
	{
	private:
		std::shared_ptr<Texture> m_texture;
		std::array<glm::vec2, 4> m_texCoords;
	public:
		Sprite();
		Sprite(std::shared_ptr<Texture> texture);
		Sprite(std::shared_ptr<Texture> texture, const std::array<glm::vec2, 4>& texCoords);

		void GenTexCoords();
		void SetTexCoords(const std::array<glm::vec2, 4>& uv);
		void SetTexture(std::shared_ptr<Texture> texture);

		inline const std::shared_ptr<Texture> GetTexture() const { return m_texture; }
		inline const std::array<glm::vec2, 4>& GetUV() const { return m_texCoords; }
	};
}
