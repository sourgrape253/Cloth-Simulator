#version 430 core

out vec4 color;
in vec3 _Out_Color;

void main()
{
    color = vec4(_Out_Color, 1.0);
}