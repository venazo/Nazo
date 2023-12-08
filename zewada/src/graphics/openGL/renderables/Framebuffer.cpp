#include <zpch.h>
#include "FrameBuffer.h"

namespace Zewada {

	Framebuffer::Framebuffer(unsigned int width, unsigned int height)
		:m_width(width), m_height(height)
	{
		Init();
	}

	void Framebuffer::Init()
	{
		glCreateFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, (GLuint)m_fbo);

		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);
		glGenTextures(1, &m_entityID);
		glBindTexture(GL_TEXTURE_2D, m_entityID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, m_width, m_height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_entityID, 0);
		
		// Build the texture that will serve as the depth attachment for the framebuffer.
		glGenTextures(1, &m_depthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_depthAttachment);
		glTexStorage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_width, m_height);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachment, 0);

		GLuint rbo_depth;
		glGenRenderbuffers(1, &rbo_depth);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo_depth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_width, m_height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo_depth);

		glBindTexture(GL_TEXTURE_2D, 0);

		glReadBuffer(GL_NONE);
		GLenum buffers[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
		glDrawBuffers(2, buffers);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			Z_ERROR() << "Framebuffer is not complete!";
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::Resize(unsigned int width, unsigned int height)
	{
		if (m_width == width && m_height == height)
		{
			return;
		}
		m_width = width;
		m_height = height;

		glDeleteFramebuffers(1, &m_fbo);
		glDeleteTextures(1, &m_texture);
		glDeleteTextures(1, &m_entityID);
		glDeleteTextures(1, &m_depthAttachment);

		Init();
	}

	int Framebuffer::ReadPixel(unsigned int attachmentIndex, int x, int y)
	{
		y = m_height - y;
		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);

		return pixelData;
	}

	void Framebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	}

	void Framebuffer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		int value = -1;
		glClearTexImage(m_entityID, 0, GL_RED_INTEGER, GL_INT, &value);
	}

	void Framebuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
