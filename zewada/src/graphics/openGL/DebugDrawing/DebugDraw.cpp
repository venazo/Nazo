#include <zpch.h>
#include "DebugDraw.h"

namespace Zewada {
	DebugDraw::DebugDraw(std::shared_ptr<Shader> shader)
	{
		m_shader = shader;
		m_vertexArray = new float[MAX_VERTECIES];

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * MAX_VERTECIES, NULL, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const GLvoid*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glLineWidth(2.0f);
	}

	void DebugDraw::AddLine(const glm::vec2& from, const glm::vec2& to, const glm::vec3& color, float t)
	{
		m_lines.push_back(Line2D(from, to, color, t));
	}

	void DebugDraw::Add2DBox(const glm::vec2& center, const glm::vec2& dimensions, float rotation, const glm::vec3& color, unsigned int t)
	{
		glm::vec2 min = glm::vec2(center) - (glm::vec2(dimensions) / 2.0f);
		glm::vec2 max = glm::vec2(center) + (glm::vec2(dimensions) / 2.0f);
	
		std::array<glm::vec2, 4> vertices = 
		{
			glm::vec2(max.x, max.y),
			glm::vec2(max.x, min.y),
			glm::vec2(min.x, min.y),
			glm::vec2(min.x, max.y)
		};

		if (rotation != 0.0f)
		{
			Zewada::Rotate2DBox(center, vertices, rotation);		
		}

		AddLine(vertices[0], vertices[1], color, t);
		AddLine(vertices[1], vertices[2], color, t);
		AddLine(vertices[2], vertices[3], color, t);
		AddLine(vertices[3], vertices[0], color, t);
	}

	void DebugDraw::AddCircle(const glm::vec2& center, float radius, const glm::vec3& color, unsigned int t)
	{
		unsigned int length = 20;
		glm::vec2 points[20];
		unsigned int increments = 360 / length;
		unsigned int currentAngle = 0;

		for (int i = 0; i < length; i++)
		{
			glm::vec2 tmp(radius, 0);
			Zewada::Rotate(tmp, currentAngle, glm::vec2());
			tmp += center;
			points[i] = tmp;

			if (i > 0)
			{
				AddLine(points[i - 1], points[i], color, t);
			}

			currentAngle += increments;
		}

		AddLine(points[length - 1], points[0], color, t);
	}

	void DebugDraw::AddCamera(const Transform& transform)
	{
		Add2DBox(transform.pos, transform.scale, 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0);
	}

	void DebugDraw::EndFrame(float dt)
	{
		for (int i = 0; i < m_lines.size(); i++)
		{
			if (!m_lines[i].EndFrame(dt))
			{
				m_lines.erase(m_lines.begin() + i);
			}
		}
	}

	void DebugDraw::Draw(const Camera& camera)
	{
		if (m_lines.size() <= 0)
			return;
		
		int index = 0;
		for (Line2D line : m_lines)
		{
			glm::vec3 color = line.color;

			glm::vec2 from = line.from;

			m_vertexArray[index] = from.x;
			m_vertexArray[index + 1] = from.y;
			m_vertexArray[index + 2] = 10;

			m_vertexArray[index + 3] = color.x;
			m_vertexArray[index + 4] = color.y;
			m_vertexArray[index + 5] = color.z;

			index += 6;

			glm::vec2 to = line.to;

			m_vertexArray[index] = to.x;
			m_vertexArray[index + 1] = to.y;
			m_vertexArray[index + 2] = 10;

			m_vertexArray[index + 3] = color.x;
			m_vertexArray[index + 4] = color.y;
			m_vertexArray[index + 5] = color.z;

			index += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, index * sizeof(float), m_vertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_shader->Enable();
		m_shader->SetUniformMat4("uProjection", camera.projectionMatrix);
		m_shader->SetUniformMat4("uView", camera.viewMatrix);

		glBindVertexArray(m_VAO);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glDrawArrays(GL_LINES, 0, index / 6);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		m_shader->Disable();
		glBindVertexArray(0);
	}

	void DebugDraw::Clear()
	{
		m_lines.clear();
	}
}