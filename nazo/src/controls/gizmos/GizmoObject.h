#pragma once

#include <Zewada.h>

using namespace Zewada;

namespace Nazo {
	struct GizmoObject
	{
		Entity ID;
		Transform transform;
		SpriteRenderer spriteRenderer;
	};
}