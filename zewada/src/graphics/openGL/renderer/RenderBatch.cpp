#include <zpch.h>
#include "RenderBatch.h"

namespace Zewada {
	RenderBatch::RenderBatch()
	{
		m_vertices = new Vertex[MAX_SPRITES * 4];
		m_index = 0;
		m_hasRoom = true;

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, MAX_SPRITES * SPRITE_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);
		glEnableVertexAttribArray(SHADER_UV_INDEX);
		glEnableVertexAttribArray(SHADER_TID_INDEX);
		glEnableVertexAttribArray(SHADER_ENTITY_ID);
		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)0);
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)(offsetof(Vertex, Vertex::color)));
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)offsetof(Vertex, Vertex::UV));
		glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)(offsetof(Vertex, Vertex::TID)));
		glVertexAttribPointer(SHADER_ENTITY_ID, 1, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)(offsetof(Vertex, Vertex::entityID)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLuint* indices = new GLuint[MAX_SPRITES * 6];

		int offset = 0;
		for (int i = 0; i < MAX_SPRITES * 6; i += 6)
		{
			indices[i] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_SPRITES * 6 * sizeof(GLuint), indices, GL_STATIC_DRAW);

		delete[] indices;

		glBindVertexArray(0);
	}

	RenderBatch::~RenderBatch()
	{
		
	}

	void RenderBatch::Submit(Transform* transform, SpriteRenderer* sprite, Entity entityID)
	{
		m_spriteRenderers.push_back(sprite);
		m_transforms.push_back(transform);
		m_entityID.push_back(entityID);
		if (m_spriteRenderers.size() >= MAX_SPRITES)
			m_hasRoom = false;
	}

	void RenderBatch::Render()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		m_vertices = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

		for (int i = 0; i < m_spriteRenderers.size(); i++)
		{
			const glm::vec3& position = m_transforms[i]->worldPos;
			const glm::vec2& size = m_transforms[i]->worldScale;
			const float& rotation = m_transforms[i]->rotation;
			const glm::vec4& color = m_spriteRenderers[i]->color;
			const std::array<glm::vec2, 4> uv = m_spriteRenderers[i]->sprite->GetUV();
			const std::shared_ptr<Texture> texture = m_spriteRenderers[i]->sprite->GetTexture();
			const Entity entityID = m_entityID[i];
			unsigned int c = 0;
			unsigned int tid = 0;
			bool found = false;
			if (texture->GetID() != 0)
			{
				for (int i = 0; i < m_textures.size(); i++)
				{
					if (m_textures[i] == texture)
					{
						tid = i + 1;
						found = true;
						break;
					}
				}

				if (!found)
				{
					m_textures.push_back(texture);
				}
			}

			glm::mat4 transformMatrix = glm::mat4(1.0f);
			bool isRotated = false;
			if (rotation != 0.0f)
				isRotated = true;
			glm::vec4 currentPos = glm::vec4(position.x + (size.x * -0.5f), position.y + (size.y * -0.5f), position.z, 1.0f);
			if (isRotated)
			{
				transformMatrix = glm::translate(transformMatrix, position);
				transformMatrix = glm::rotate(transformMatrix, (float)(rotation / 180.0f * M_PI), glm::vec3(0, 0, 1));
				transformMatrix = glm::scale(transformMatrix, glm::vec3(size.x, size.y, 0.0f));

				currentPos = transformMatrix * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
			}

			m_vertices->position = glm::vec3(currentPos.x, currentPos.y, currentPos.z);
			m_vertices->UV = uv[0];
			m_vertices->TID = tid;
			m_vertices->color = color;
			m_vertices->entityID = entityID;
			m_vertices++;

			currentPos = glm::vec4(position.x + (size.x * -0.5f), position.y + (size.y * 0.5f), position.z, 1.0f);

			if (isRotated)
			{
				currentPos = transformMatrix * glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f);
			}

			m_vertices->position = glm::vec3(currentPos.x, currentPos.y, currentPos.z);
			m_vertices->UV = uv[1];
			m_vertices->TID = tid;
			m_vertices->color = color;
			m_vertices->entityID = entityID;
			m_vertices++;

			currentPos = glm::vec4(position.x + (size.x * 0.5f), position.y + (size.y * 0.5f), position.z, 1.0f);
			if (isRotated)
			{
				currentPos = transformMatrix * glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
			}

			m_vertices->position = glm::vec3(currentPos.x, currentPos.y, currentPos.z);
			m_vertices->UV = uv[2];
			m_vertices->TID = tid;
			m_vertices->color = color;
			m_vertices->entityID = entityID;
			m_vertices++;

			currentPos = glm::vec4(position.x + (size.x * 0.5f), position.y + (size.y * -0.5f), position.z, 1.0f);
			if (isRotated)
			{
				currentPos = transformMatrix * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
			}

			m_vertices->position = glm::vec3(currentPos.x, currentPos.y, currentPos.z);
			m_vertices->UV = uv[3];
			m_vertices->TID = tid;
			m_vertices->color = color;
			m_vertices->entityID = entityID;
			m_vertices++;

			m_index += 6;
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		for (int i = 0; i < m_textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE1 + i);
			m_textures[i]->Bind();
		}

		glBindVertexArray(m_VAO);

		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);
		glEnableVertexAttribArray(SHADER_UV_INDEX);
		glEnableVertexAttribArray(SHADER_TID_INDEX);
		glEnableVertexAttribArray(SHADER_ENTITY_ID);

		glDrawElements(GL_TRIANGLES, m_index, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(SHADER_VERTEX_INDEX);
		glDisableVertexAttribArray(SHADER_COLOR_INDEX);
		glDisableVertexAttribArray(SHADER_UV_INDEX);
		glDisableVertexAttribArray(SHADER_TID_INDEX);
		glEnableVertexAttribArray(SHADER_ENTITY_ID);

		glBindVertexArray(0);

		for (int i = 0; i < m_textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE1 + i);
			m_textures[i]->UnBind();
		}
		m_index = 0;
	}

	void RenderBatch::Clear()
	{
		m_spriteRenderers.clear();
		m_transforms.clear();
		m_entityID.clear();
		
		m_hasRoom = true;
	}
}