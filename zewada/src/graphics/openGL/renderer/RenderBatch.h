#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include "../Renderables/Sprite.h"
#include "Shader.h"
#include "../../../ECS/Components.h"
#include "../../../Utils/Math.h"
#include "../../../ECS/core/Coordinator.h"
#include "../../../utils/debug/Logger.h"

#define MAX_SPRITES 10000
#define VERTEX_SIZE sizeof(Vertex)
#define SPRITE_SIZE VERTEX_SIZE * 4

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX 1
#define SHADER_UV_INDEX 2
#define SHADER_TID_INDEX 3
#define SHADER_ENTITY_ID 4

namespace Zewada {
	struct Vertex
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 UV;
		float TID;
		float entityID;
	};

	class RenderBatch
	{
	private:
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_EBO;

		bool m_hasRoom;
		std::vector<SpriteRenderer*> m_spriteRenderers;
		std::vector<Transform*> m_transforms;
		std::vector<Entity> m_entityID;

		unsigned int m_index;
		std::vector<std::shared_ptr<const Texture>> m_textures;
		Vertex* m_vertices;
	public:
		RenderBatch();
		~RenderBatch();
		void Submit(Transform* transform, SpriteRenderer* sprite, Entity entityID = -1);
		void Render();
		void Clear();

		inline bool HasRoom() { return m_hasRoom; }
	};
}