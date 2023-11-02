#pragma once

#include "RenderBatch.h"
#include <zpch.h>
#include "../../../Scene/SceneManager.h"

namespace Zewada {

	class Renderer2D
	{
	private:
		std::shared_ptr<Shader> m_activeShader;

		glm::vec4 m_backgroundColor;

		int m_highestIndex;
		int m_lowestIndex;
		std::unordered_map<int, std::shared_ptr<RenderBatch>> m_batches;
	public:
		Renderer2D();
		void Submit(Transform* transform, SpriteRenderer* sprite, int entityID = -1);
		void Render(const Camera& cam);
		void Clear();

		inline glm::vec4& GetBackgroundColor(){return m_backgroundColor;}			
		void SetBackgroundColor(const glm::vec4& BackgroundColor);

		void BindShader(std::shared_ptr<Shader> shader);
	};

}