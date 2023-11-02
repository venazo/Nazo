#pragma once

#include "Texture.h"
#include "../../../Utils/Debug/Logger.h"

#include <glm/glm.hpp>

namespace Zewada {

	class Framebuffer
	{
	private:
		GLuint m_fbo = 0;
		GLuint m_texture;
		GLuint m_entityID;
		GLuint m_depthAttachment;

		unsigned int m_width, m_height;
	public:
		Framebuffer(unsigned int width, unsigned int height);
		void Init();
		void Resize(unsigned int width, unsigned int height);

		int ReadPixel(unsigned int attachmentIndex, int x, int y);

		void Bind();
		void Clear();
		void UnBind();

		inline const GLuint& GetFbo() { return m_fbo; }
		inline const GLuint& GetTID() { return m_texture; }
	};
}