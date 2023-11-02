#pragma once

#include "Sprite.h"
#include <vector>
#include "../../../Utils/Debug/Logger.h"

namespace Zewada {

	class SpriteSheet
	{
	private:
		std::shared_ptr<Texture> m_texture = std::make_shared<Texture>();
		std::vector<std::shared_ptr<Sprite>> m_sprites;

		int m_width, m_height, m_spacing, m_numSprites = 0;
	public:
		SpriteSheet(std::shared_ptr<Texture> texture, int spriteWidth, int spriteHeight, int numSprites, int spacing);
		SpriteSheet() = default;

		const std::shared_ptr<Sprite> GetSprite(unsigned int index);

		inline int GetSpriteWidth() {return m_width;};
		inline int GetSpriteHeight() { return m_height;};
		inline int GetNumSprites() {return m_numSprites;};
		inline int GetSpacing() {return m_spacing;};

		inline std::vector<std::shared_ptr<Sprite>>& GetSprites() { return m_sprites; };
		inline std::shared_ptr<Texture> GetTexture() { return m_texture; };
	};
}
