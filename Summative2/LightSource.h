#pragma once

#include <iostream>

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "ShaderLoader.h"
#include "Dependencies\soil\SOIL.h"

// Math libraries
#include "Dependencies\glm\glm\glm.hpp"
#include "Dependencies\glm\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\glm\gtc\type_ptr.hpp"

#include "GameScene.h"
#include <iostream>
#include <string>
#include <vector>

class GameScene;
enum ModelType;
struct Position;

class Light
{
public:

	Light(glm::vec3 _LightPos, glm::vec3 _LightColor, glm::vec3 _LightDir);
	~Light();	

	GameScene* _rscene;

	void SetLightPos(GLfloat x_Pos, GLfloat y_Pos, GLfloat z_Pos);
	glm::vec3 GetLightPos();

	void SetLightColor(GLfloat R, GLfloat G, GLfloat B);
	glm::vec3 GetLightColor();

	void SetLightDirection(GLfloat x, GLfloat y, GLfloat z);
	glm::vec3 GetLightDirection();

	glm::vec3 lightPos;
	glm::vec3 lightColor;
	glm::vec3 lightDir;


private:

};



