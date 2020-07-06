#version 430 core
layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 Color;

uniform mat4 mvp;
uniform vec3 Color;

out vec3 _Out_Color;

void main()
{
	gl_Position = mvp * vec4(position, 1.0f);
	_Out_Color = Color;
}