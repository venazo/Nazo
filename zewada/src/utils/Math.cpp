#include <zpch.h>
#include "Math.h"

namespace Zewada {
	void Rotate2DBox(const glm::vec2& center, std::array<glm::vec2, 4>& vertecies,
		float rotation)
	{
		//center!
		for(int i = 0; i < 4; i++)
		{
			vertecies[i] -= center;
		}

		float vd = sqrt((vertecies[0].x * vertecies[0].x) +
			(vertecies[0].y * vertecies[0].y));
		float angle = asin(vertecies[0].y / vd) * 180.0f / M_PI;

		rotation = rotation / 180.0f * M_PI;
		angle = angle / 180.0f * M_PI;

		vertecies[0].x = vd * cos(angle + rotation);
		vertecies[0].y = vd * sin(angle + rotation);

		vertecies[1].x = vd * cos(M_PI - angle + rotation);
		vertecies[1].y = vd * sin(M_PI - angle + rotation);

		vertecies[2].x = vd * cos(M_PI + angle + rotation);
		vertecies[2].y = vd * sin(M_PI + angle + rotation);

		vertecies[3].x = vd * cos(2.0f * M_PI - angle + rotation);
		vertecies[3].y = vd * sin(2.0f * M_PI - angle + rotation);

		for (int i = 0; i < 4; i++)
		{
			vertecies[i] += center;
		}
	}

	void Rotate(glm::vec2& vec, float angle,
		const glm::vec2& center)
	{
		if (angle == 0.0f)
			return;
		vec -= center;
		float radius = vec.x;
		vec.y = radius * sin(angle / 180.0f * M_PI);
		vec.x = vec.y / tan(angle / 180.0f * M_PI);
		vec += center;
	}
}