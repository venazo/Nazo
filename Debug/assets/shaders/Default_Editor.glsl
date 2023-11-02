#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aUV;
layout (location = 3) in float aTID;
layout (location = 4) in float aEntityID;

uniform mat4 uProjection = mat4(1.0f);
uniform mat4 uView = mat4(1.0f);

out vec4 fColor;
out vec3 fPosition;
out vec2 fUV;
out float fTID;
out float fEntityID;

void main()
{
	fColor = aColor;
	fPosition = aPos;
	fUV = aUV;
	fTID = aTID;
	fEntityID = aEntityID;
	gl_Position = uProjection * uView * vec4(aPos, 1.0);
}
//SPLIT
#version 450 core

in vec4 fColor;
in vec3 fPosition;
in vec2 fUV;
in float fTID;
in float fEntityID;

layout (location = 0) out vec4 color;
layout (location = 1) out int entityID;

uniform sampler2D textures[16];

void main()
{
	vec4 texColor = vec4(1, 1, 1, 1);
	if(fTID > 0)
	{
		int tid = int(fTID);
		texColor = fColor * texture(textures[tid], fUV);
	}
	else
	{
		texColor = fColor;
	}
	if(texColor.a > 0.5)
	{
		entityID = int(fEntityID);
	}
	color = texColor;
}