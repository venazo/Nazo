#include <zpch.h>
#include "Renderer2D.h"

namespace Zewada {
	Renderer2D::Renderer2D()
	{
		m_backgroundColor = glm::vec4(0.17f, 0.17f, 0.17f, 1.0f);
		m_highestIndex = 0;
		m_lowestIndex = 0;
	}

	void Renderer2D::Submit(Transform* transform, SpriteRenderer* sprite, int entityID)
	{
		int zindex = transform->worldPos.z;
		if (zindex < m_lowestIndex)
			m_lowestIndex = zindex;
		if (zindex > m_highestIndex)
			m_highestIndex = zindex;
		if (Utils::Contains(m_batches, zindex))
		{
			if(m_batches[zindex] != nullptr)
			{
				if (m_batches[zindex]->HasRoom())
				{
					m_batches[zindex]->Submit(transform, sprite, entityID);
					return;
				}
			}
		}
		std::shared_ptr<RenderBatch> batch = std::make_shared<RenderBatch>();
		batch->Submit(transform, sprite, entityID);
		if(m_batches[zindex] == nullptr)
		{
			m_batches[zindex] = batch;
		}
		m_batches.insert({ zindex, batch });
	}

	void Renderer2D::Render(const Camera& cam)
	{
		glClearColor(m_backgroundColor.x, m_backgroundColor.y, m_backgroundColor.z, m_backgroundColor.w);
		m_activeShader->Enable();
		m_activeShader->SetUniformMat4("uProjection", cam.projectionMatrix);
		m_activeShader->SetUniformMat4("uView", cam.viewMatrix);
		for (int i = m_lowestIndex; i <= m_highestIndex; i++)
		{
			if (m_batches[i] != nullptr)
				m_batches[i]->Render();
		}
		m_activeShader->Disable();
	}

	void Renderer2D::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (int i = m_lowestIndex; i <= m_highestIndex; i++)
		{
			if (m_batches[i] != nullptr)
				m_batches[i]->Clear();
		}
		m_lowestIndex = 0;
		m_highestIndex = 0;		
	}

	void Renderer2D::BindShader(std::shared_ptr<Shader> shader)
	{
		m_activeShader = shader;
	}

	void Renderer2D::SetBackgroundColor(const glm::vec4& backgroundColor)
	{
		m_backgroundColor = backgroundColor;
	}

}