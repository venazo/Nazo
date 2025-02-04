#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 uProjection = mat4(1.0f);
uniform mat4 uView = mat4(1.0f);

out vec3 fColor;

void main()
{
	fColor = aColor;

	gl_Position = uProjection * uView * vec4(aPos, 1.0f);
}
//SPLIT
#version 330 core

in vec3 fColor;

out vec4 color;

void main()
{
	color = vec4(fColor, 1.0f);
}