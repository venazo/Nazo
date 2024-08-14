#include "Font.h"
#include "zpch.h"
#include "../../../ECS/Components.h"

namespace Zewada
{
    void Font::Load()
    {
        FT_Library ft;
        if(FT_Init_FreeType(&ft))
        {
            Z_ERROR() << "Could not init FreeType library!";
            return;
        }

        FT_Face face;
        if(FT_New_Face(ft, m_path.c_str(), 0, &face))
        {
            Z_WARN() << "Failed to load:" << m_path;
            return;
        }

        float fontSize = 48;

        FT_Set_Pixel_Sizes(face, 0, fontSize);

        int padding = 1;
        int row = 0;
        int col = padding;

        const int textureWidth = 512;
        char textureBuffer[textureWidth * textureWidth];

        std::shared_ptr<Texture> texture = std::make_shared<Texture>(); 

        for (char glyphIdx = 32; glyphIdx < 127; glyphIdx++)
        {
            FT_UInt glyphIndex = FT_Get_Char_Index(face, glyphIdx);
            FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT);
            FT_Error error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

            if(col + face->glyph->bitmap.width + padding >= 512)
            {
                col = padding;
                row += fontSize;
            }

            for(unsigned int y = 0; y < face->glyph->bitmap.rows; y++)
            {
                for(unsigned int x = 0; x < face->glyph->bitmap.width; x++)
                {
                    textureBuffer[(row + y) * textureWidth + col + x] = face->glyph->bitmap.buffer[ y * face->glyph->bitmap.width + x];
                }
            }

            std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(texture);

            float xpos = col;
            float ypos = row;
            float w = face->glyph->bitmap.width;
            float h = face->glyph->bitmap.rows;

            xpos /= textureWidth;
            ypos /= textureWidth;
            w /= textureWidth;
            h /= textureWidth;

            std::array<glm::vec2, 4> texCoords = 
            {
                glm::vec2(xpos, ypos + h) ,
                glm::vec2(xpos, ypos),
                glm::vec2(xpos + w, ypos),
                glm::vec2(xpos + w, ypos + h)
            };

            sprite->SetTexCoords(texCoords);

            Character character = {
                sprite,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                (face->glyph->advance.x >> 6)
            };
        
            m_characters.insert(std::pair<char, Character>(glyphIdx, character));

            col += face->glyph->bitmap.width + padding;
        }

        texture->LoadFont(textureBuffer, textureWidth);

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }

    Font::Font()
    {
        m_path = (std::string)std::filesystem::current_path().string() + "\\Assets\\Fonts\\OpenSans-Regular.TTF";
        Load();
    }

    Font::Font(const std::string& path)
    {
        m_path = (std::string)std::filesystem::current_path().string() + "/" + path;
        Load();
    }
}