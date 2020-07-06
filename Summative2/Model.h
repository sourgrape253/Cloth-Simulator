#pragma once

#include <iostream>

#include "GameScene.h"
#include <string>
#include <vector>

class GameScene;
enum ModelType;
struct Position;
struct VertexFormat;

class Model
{
public:
	
	Model();
	Model(ModelType Shape, char* Filename, GLfloat x, GLfloat y, GLfloat z, GLfloat X_Scale, GLfloat Y_Scale, GLfloat Z_Scale, glm::vec3 _Rotation);
	~Model();

	unsigned char keyState[255];
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLuint texture;
	ModelType m_Shape;
	glm::mat4 model;
	glm::mat4 vertexColor;
	
	char* texFileName;

	GameScene* _rscene;
	glm::vec3 m_ModelPosition;
	glm::vec3 m_Scale;
	glm::vec3 ModelFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 ModelUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 ModelSpeed = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 Rotation;

	std::vector<GLfloat> vertices;
	std::vector<GLuint> vertexIndices;
	std::vector<VertexFormat> VertForm;

	void Render(GLuint program);
	void UpdateModel();
	void Init();
	
	void MoveLightSource();
	void ApplyTexture();

private:

};

