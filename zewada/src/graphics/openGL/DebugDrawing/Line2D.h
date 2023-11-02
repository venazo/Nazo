#pragma once

#include <glm/glm.hpp>

namespace Zewada {
	struct Line2D 
	{
	public:
		glm::vec2 from, to;
		glm::vec3 color;
		float t;

	public:
		Line2D()
		{

		}

		Line2D(const glm::vec2& c_from, const glm::vec2& c_to, const glm::vec3& c_color, float c_t)
		{
			from = c_from;
			to = c_to;
			color = c_color;
			t = c_t;
		}

		//false = dead
		bool EndFrame(float dt)
		{
			t -= dt;
			if (t < 0.0f)
				return false;
			else
				return true;
		}
	};
}