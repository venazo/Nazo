#pragma once

#include <vector>
#include "Line2D.h"
#include "../renderer/Renderer2D.h"
#include "../../../utils/resource/AssetPool.h"

#define MAX_LINES 500
#define MAX_VERTECIES MAX_LINES * 6 * 2

namespace Zewada {
	
	class DebugDraw
	{
	private:
		unsigned int m_VAO;
		unsigned int m_VBO;
		std::shared_ptr<Shader> m_shader;
		std::vector<Line2D> m_lines;
		float* m_vertexArray;

	public:
		DebugDraw(std::shared_ptr<Shader> shader);
		void EndFrame(float dt);
		void Draw(const Camera& camera);
		void Clear();

		void AddCamera(const Transform& transform);

		void AddLine(const glm::vec2& from, const glm::vec2& to, const glm::vec3& color, float t = 0);
		void Add2DBox(const glm::vec2& center, const glm::vec2& dimensions, float rotation, const glm::vec3& color, unsigned int t = 0);
		void AddCircle(const glm::vec2& center, float radius, const glm::vec3& color, unsigned int t = 0);
		void AddOpenPolygon(const glm::vec2& center, std::vector<glm::vec2> vertices, const glm::vec3& color, unsigned int t = 0);
		void AddEdge(const glm::vec2& center, std::vector<glm::vec2> vertices, const glm::vec3& color, unsigned int t = 0);
		void AddPolygon(const glm::vec2& center, std::vector<glm::vec2> vertices, const glm::vec3& color, unsigned int t = 0);
    };
}