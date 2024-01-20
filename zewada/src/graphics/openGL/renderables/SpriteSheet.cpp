#include <zpch.h>
#include "SpriteSheet.h"

namespace Zewada {

	SpriteSheet::SpriteSheet(std::shared_ptr<Texture> texture, int spriteWidth, int spriteHeight, int numSprites, int spacing)
	{
		m_texture = texture;

		m_width = spriteWidth;
		m_height = spriteHeight;
		m_numSprites = numSprites;
		m_spacing = spacing;

		int currentX = 0;
		int currentY = texture->GetHeight() - spriteHeight;
		for (int i = 0; i < numSprites; i++)
		{
			float topY = (float)(currentY + spriteHeight) / (float)texture->GetHeight();
			float rightX = (float)(currentX + spriteWidth) / (float)texture->GetWidth();
			float leftX = currentX / (float)texture->GetWidth();
			float bottomY = currentY / (float)texture->GetHeight();

			std::array<glm::vec2, 4> texCoords =
			{
				glm::vec2(leftX, bottomY),
				glm::vec2(leftX, topY),
				glm::vec2(rightX, topY),
				glm::vec2(rightX, bottomY)
			};

			std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(texture, texCoords);
			m_sprites.push_back(sprite);

			currentX += spriteWidth + spacing;
			if (currentX >= texture->GetWidth())
			{
				currentX = 0;
				currentY -= (spriteHeight + spacing);
			}
		}
	}

	std::shared_ptr<Sprite> SpriteSheet::GetSprite(unsigned int index)
	{
		if (index < m_sprites.size())
		{
			return m_sprites[index];
		}

		Z_WARN() << "SpriteSheet " + m_texture->GetPath() + " does not have " + std::to_string(index + 1) + " Sprites!";
		return std::make_shared<Sprite>();
	}
}
