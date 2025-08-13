#pragma once

#include <glm/glm.hpp>
#include <array>

#define _USE_MATH_DEFINES
#include <math.h>

#define PI 3.14159265359

namespace Zewada {
	template <typename T> int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}

	void Rotate2DBox(const glm::vec2& center, std::array<glm::vec2, 4>& vertecies,
	float rotation);
	void Rotate(glm::vec2& vec, float angle, 
		const glm::vec2& center);

}