#pragma once

#include <iostream>
#include <vector>
#include "GameScene.h"

// Math libraries
#include "Dependencies\glm\glm\glm.hpp"
#include "Dependencies\glm\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\glm\gtc\type_ptr.hpp"


#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#define WIDTH 800
#define HEIGHT 600

class Model;
class SkyBox;

struct Position
{
	GLfloat _xCoOrd;
	GLfloat _yCoOrd;
	GLfloat _zCoOrd;
};

struct TexCoord
{
	GLfloat u;
	GLfloat v;
};

struct Normals
{
	float x, y, z;

	Normals(float _x, float _y, float _z){
		x = _x;
		y = _y;
		z = _z;
	}

	Normals() {}
};

struct VertexFormat
{
	Position newPos;
	TexCoord newTex;
	Normals normal;

	VertexFormat(GLfloat x, GLfloat y, GLfloat z, GLfloat texX, GLfloat texY, Normals _normal)
	{
		x = newPos._xCoOrd;
		y = newPos._yCoOrd;
		z = newPos._zCoOrd;

		texX = newTex.u;
		texY = newTex.v;
		normal = _normal;
	};

	VertexFormat(Position _Pos, TexCoord _Text, Normals _Norms)
	{
		newPos = _Pos;
		newTex = _Text;
		normal = _Norms;
	}

	VertexFormat()
	{

	}

};

enum ModelType
{
	CUBE,
	PYRAMID,
	SPHERE, 
	SQUARE,
	TRIANGLE,
	LIGHT
};

void SetCube(Model& _rModel);
void SetSquare(Model& _rModel);
void SetTriangle(Model& _rModel);
void SetPyramid(Model& _rModel);
void SetSphere(Model& _rModel);
void SetSkyBox(SkyBox& _Skybox);
void setSphereData(std::vector<VertexFormat>& vertices, std::vector<GLuint>& indices, Model& _rModel);
