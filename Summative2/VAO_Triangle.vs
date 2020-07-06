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
 out vec3 FragPos;
 out vec3 Normal;

void main(void)
{
	//vec3 newpos = {position.x * cos(currentTime) + position.y * sin(currentTime),
    //-position.x * sin(currentTime) + position.y * cos(currentTime),
    // 0.0};

    //gl_Position = vec4(position, 1.0);

	gl_Position = projection * view * model * vec4(position, 1.0);
   // vertexColor = color;
	TexCoord = texCoord; 


	// Lighting
	FragPos = vec3(model*vec4(position, 1.0f));
	Normal = mat3(transpose(inverse(model))) * normal;
}