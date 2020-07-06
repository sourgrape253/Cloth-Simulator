#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;
 
 uniform float currentTime;
 uniform mat4 model;
 uniform mat4 view;
 uniform mat4 projection;

 
 out vec3 vertexColor;
 out vec2 TexCoord;

 // Lighting
 out vec4 FragPos;
 out vec3 Normal;


void main(void)
{
	TexCoord = texCoord; 

   // Fog
   FragPos = (model*vec4(position,1.0f));
   gl_Position = projection * view * FragPos;

	// Lighting
	//FragPos = vec3(model*vec4(position, 1.0f));

	Normal = mat3(transpose(inverse(model))) * normal;
}