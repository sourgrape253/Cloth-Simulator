#pragma once

#include "GameScene.h"
#include <iostream>

class ShaderLoader
{
private:

	std::string ReadShader(char *filename);
	GLuint CreateShader(GLenum shaderType,
		std::string source,
		char* shaderName);

public:

	ShaderLoader(void);
	~ShaderLoader(void);
	GLuint CreateProgram(char* VertexShaderFilename,
						 char* FragmentShaderFilename);

	// constructor for geometry shader creations
	GLuint CreateProgram(char* VertexShaderFilename,
						 char* FragmentShaderFilename,
						 char* geometryShaderFilename);

	// constructor for Tesselation shader creations
	GLuint CreateProgram(char* VertexShaderFilename,
		char* FragmentShaderFilename,
		char* TessControlShaderFileName,
		char* TessEvalShaderFileName);

};

