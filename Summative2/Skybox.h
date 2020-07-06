#pragma once

#include <iostream>

#include "GameScene.h"
#include <string>
#include <vector>

class GameScene;
enum ModelType;
struct Position;

class SkyBox
{
public:

	SkyBox();
	SkyBox(ModelType Shape, char* Right, char* Left, char* Top, char* Bottom, char* back, char* Front, GLfloat x, GLfloat y, GLfloat z);
	~SkyBox();

	unsigned char keyState[255];
	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	GLuint texture;
	ModelType m_Shape;

	glm::mat4 model;
	glm::mat4 vertexColor;
	glm::mat4 world;

	Position* modelPos;
	char* texFileName;

	GameScene* _rscene;

	glm::vec3 m_ModelPosition;
	glm::vec3 ModelFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 ModelUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 ModelSpeed = glm::vec3(0.1f, 0.1f, 0.1f);
	std::vector<GLfloat> vertices;
	std::vector<GLuint> vertexIndices;

	void ApplyShader();
	void RenderSkybox(GLuint program);
	void UpdateModel();
	void Init();
	GLfloat* GetVertices();
	GLuint* GetIndices();
	void ApplyTexture();


	std::vector<char*> textures_faces;

private:

};