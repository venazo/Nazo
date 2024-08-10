#pragma once

#include <ft2build.h>
#include <freetype/freetype.h>
#include <utils/debug/Logger.h>
#include <glm/glm.hpp>
#include <map>
#include <glad/glad.h>
#include "Sprite.h"

namespace Zewada
{
    struct Character {
        std::shared_ptr<Sprite> sprite;
        glm::ivec2   size;
        glm::ivec2   bearing;
        float advance;
    };

    class Font
    {
    private:
        std::string m_path;
        std::map<char, Character> m_characters;

        void Load();        
    public:
        Font();
        Font(const std::string& path);
        inline const std::map<char, Character> GetCharacters() {return m_characters;}
    };
}