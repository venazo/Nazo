#pragma once

#include <glad/glad.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <utils/debug/Logger.h>

namespace Zewada {

	class AssetPool;

	class Texture
	{
	private:
		std::string m_Path;
		GLuint m_TID;
		GLsizei m_Width, m_Height;

		GLuint Load();
	public:
		Texture(const std::string& path);
		Texture(unsigned int width, unsigned int height);
		Texture();
		~Texture();
		
		void LoadFont(char* textureBuffer, unsigned int textureSize);

		inline const unsigned int GetWidth() const { return m_Width; }
		inline const unsigned int GetHeight() const { return m_Height; }
		inline const unsigned int GetID() const { return m_TID; }
		inline const std::string GetPath() const { return m_Path; }

		void Bind() const;
		void UnBind() const;
		operator bool() const {
			if(m_TID != 0)
				return true;
			else
				return false;
		}	
	};
}
