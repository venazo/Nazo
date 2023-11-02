#include <zpch.h>
#include "Texture.h"

#include <stb_image.h>

namespace Zewada {

	Texture::Texture()
	{
		m_TID = 0;
		m_Path = "Default_Texture";
	}

	Texture::~Texture()
	{
		if(m_TID != 0)
			glDeleteTextures(1, &m_TID);
	}

	Texture::Texture(const std::string& path)
	{
		m_Path = path;
		m_TID = Load();
	}

	Texture::Texture(unsigned int width, unsigned int height)
	{
		m_Path = "Generated";
		m_Width = width;
		m_Height = height;

		glGenTextures(1, &m_TID);
		glBindTexture(GL_TEXTURE_2D, m_TID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLuint Texture::Load()
	{
		stbi_set_flip_vertically_on_load(true);
		auto texture = stbi_load(m_Path.c_str(), &m_Width, &m_Height, 0, 4);

		GLuint result;
		glGenTextures(1, &result);
		glBindTexture(GL_TEXTURE_2D, result);

		//LINEAR verschwommen
		//NEAREST pixelig
		//for gamelook
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (texture)
			stbi_image_free(texture);

		return result;
	}

	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_TID);
	}

	void Texture::UnBind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}