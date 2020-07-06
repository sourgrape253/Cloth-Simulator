#include "Utils.h"
#include "Skybox.h"

/*
* Function - SetCube()
* Set the cube vertices and indices to create a cube model

*/
void SetCube(Model& _rModel)
{
	VertexFormat FrontLeft(-1.0, 1.0, 1.0, 0.0, 0.0, Normals(0.0f, 0.0f, 1.0f));

	_rModel.vertices =
	{
		// Front Side
		// Top Left
		-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0, 0.0f, 0.0f, // 0.
		// Top Right
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0, 1.0f, 0.0f, // 1.
		// Bottom Left
		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0, 0.0f, 1.0f, // 2.
		// Bottom Right
		1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0, 1.0f, 1.0f, // 3.

		// Right Side
		// Top Left
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0, 0.0f, 0.0f, // 4
		// Top Right
		1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0, 1.0f, 0.0f, // 5
		// Bottom Left
		1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0, 0.0f, 1.0f, // 6
		// Bottom Right
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0, 1.0f, 1.0f, // 7

		// Back Side
		// Top Left
		1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0, 0.0f, 0.0f, // 8
		// Top Right
		-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0, 1.0f, 0.0f, // 9
		// Bottom Left
		1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0, 0.0f, 1.0f, // 10
		// Bottom Right
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0, 1.0f, 1.0f, // 11

		// Left Side
		// Top Left
		-1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0, 0.0f, 0.0f, // 12
		// Top Right
		-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0, 1.0f, 0.0f, // 13
		// Bottom Left
		-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0, 0.0f, 1.0f, // 14
		// Bottom Right
		-1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0, 1.0f, 1.0f, // 15

		// Bottom
		// Top Left
		-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0, 0.0f, 0.0f, // 16
		// Top Right
		1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0, 1.0f, 0.0f, // 17
		// Bottom Left
		-1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0, 0.0f, 1.0f, // 18
		// Bottom Right
		1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0, 1.0f, 1.0f, // 19

		// Top
		// Top Left
		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0, 0.0f, 0.0f,  // 20
		// Top Right
		1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0, 1.0f, 0.0f, // 21
		// Bottom Left
		-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0, 0.0f, 1.0f, // 22
		// Bottom Right
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0, 1.0f, 1.0f // 23
	};

	//10, 12, 9,
	//9, 12, 11
	_rModel.vertexIndices =
	{
		// Front
		2, 1, 0,
		2, 3, 1,
		// Right
		6, 5, 4,
		6, 7, 5,
		// Back
		10, 9, 8,
		10, 11, 9,
		// Left
		14, 13, 12,
		14, 15, 13,
		// Bottom
		17, 19, 16,
		16, 19, 18,
		// Top
		22, 21, 20,
		22, 23, 21
	};
}

/*
* Function - SetSquare()
* Set the Square vertices and indices to create a Square model

*/
void SetSquare(Model& _rModel)
{
	_rModel.vertices =
	{
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Top right.
		1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,// Bottom Right
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,// Bottom left
		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f// Top Left
	};

	_rModel.vertexIndices =
	{
		3, 1, 0, // first Triangle
		3, 2, 1 // Second Triangle
	};


}

/*
* Function - SetTriangle()
* Set the Triangle vertices and indices to create a Triangle model

*/
void SetTriangle(Model& _rModel)
{
	_rModel.vertices =
	{
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0, 0.5f, 0.5f,// Top
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0, 0.0f, 1.0f,// Bottom left
		1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0, 1.0f, 1.0f, // Bottom Right
	};

	_rModel.vertexIndices =
	{
		0, 1, 2
	};
}

/*
* Function - SetPyramid()
* Set the Pyramid vertices and indices to create a Pyramid model

*/
void SetPyramid(Model& _rModel)
{
	_rModel.vertices =
	{
		// Top
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, // 0

		// Front Side
		// Left
		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // 1
		// Right
		1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // 2

		// Right Side
		// Left
		1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 3 
		// Right
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // 4

		// Back Side
		// Left
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, // 5
		// Right
		1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // 6

		// Left Side
		// Left
		-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 7
		// Right
		-1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // 8

		// Bottom
		-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // 9

		1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // 10

		-1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // 11

		1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f // 12

	};

	_rModel.vertexIndices =
	{
		// front
		0, 1, 2,
		// right
		0, 3, 4,
		//back
		0, 6, 5,
		//left
		0, 7, 8,
		// bottom
		9, 10, 12,
		9, 12, 11
	};

}

/*
* Function - SetSkyBox()
* Set the SkyBox vertices and indices to create a SkyBox model (BEWARE OF BACKFACE CULLING) - different to cube vertices and indicces

*/
void SetSkyBox(SkyBox& _Skybox)
{
	_Skybox.vertices =
	{
		// Front Side
		// Top Left
		-1.0f, 1.0f, 1.0f,
		// Top Right
		1.0f, 1.0f, 1.0f,
		// Bottom Left
		-1.0f, -1.0f, 1.0f,
		// Bottom Right
		1.0f, -1.0f, 1.0f,

		// Right Side
		// Top Left
		1.0f, 1.0f, 1.0f,
		// Top Right
		1.0f, 1.0f, -1.0f,
		// Bottom Left
		1.0f, -1.0f, 1.0f,
		// Bottom Right
		1.0f, -1.0f, -1.0f,

		// Back Side
		// Top Left
		1.0f, 1.0f, -1.0f,
		// Top Right
		-1.0f, 1.0f, -1.0f,
		// Bottom Left
		1.0f, -1.0f, -1.0f,
		// Bottom Right
		-1.0f, -1.0f, -1.0f,

		// Left Side
		// Top Left
		-1.0f, 1.0f, -1.0f,
		// Top Right
		-1.0f, 1.0f, 1.0f,
		// Bottom Left
		-1.0f, -1.0f, -1.0f,
		// Bottom Right
		-1.0f, -1.0f, 1.0f,

		// Bottom
		// Top Left
		-1.0f, -1.0f, -1.0f,
		// Top Right
		1.0f, -1.0f, -1.0f,
		// Bottom Left
		-1.0f, -1.0f, 1.0f,
		// Bottom Right
		1.0f, -1.0f, 1.0f,

		// Top
		// Top Left
		-1.0f, 1.0f, -1.0f,
		// Top Right
		1.0f, 1.0f, -1.0f,
		// Bottom Left
		-1.0f, 1.0f, 1.0f,
		// Bottom Right
		1.0f, 1.0f, 1.0f,
	};

	_Skybox.vertexIndices =
	{
		// Front
		0, 1, 2,
		1, 3, 2,
		// Right
		4, 5, 6,
		5, 7, 6,
		// Back
		8, 9, 10,
		9, 11, 10,
		// Left
		12, 13, 14,
		13, 15, 14,
		// Bottom
		16, 19, 17,
		18, 19, 16,
		// Top
		21, 23, 20,
		20, 23, 22
	};
}


void setSphereData(std::vector<VertexFormat>& vertices, std::vector<GLuint>& indices, Model& _rModel)
{
	std::vector<VertexFormat> Vertices;
	std::vector<GLuint> Indices;

	double latitudeBands = 30;
	double longitudeBands = 30;
	double radius = 30.0f;

	

	for (double latNumber = 0; latNumber <= latitudeBands; latNumber++) {
		double theta = latNumber * 3.14 / latitudeBands;
		double sinTheta = sin(theta);
		double cosTheta = cos(theta);

		for (double longNumber = 0; longNumber <= longitudeBands; longNumber++) {
			double phi = longNumber * 2 * 3.14 / longitudeBands;
			double sinPhi = sin(phi);
			double cosPhi = cos(phi);

			VertexFormat vs;

			vs.newTex.u = 1 - (float)(longNumber / longitudeBands); // u
			vs.newTex.v = 1 - (float)(latNumber / latitudeBands);   // v

			vs.normal.x = (float)(cosPhi * sinTheta);   // x
			vs.normal.y = (float)cosTheta;            // y
			vs.normal.z = (float)(sinPhi * sinTheta);   // z

			vs.newPos._xCoOrd = (float)(radius * vs.normal.x);
			vs.newPos._yCoOrd = (float)(radius * vs.normal.y);
			vs.newPos._zCoOrd = (float)(radius * vs.normal.z);

			VertexFormat VertToPush(vs.newPos, vs.newTex, vs.normal);
			Vertices.push_back(VertToPush);
		}
	}

	for (GLuint latNumber = 0; latNumber < latitudeBands; latNumber++) {
		for (GLuint longNumber = 0; longNumber < longitudeBands; longNumber++) {
			GLuint first = (GLuint)(latNumber * (longitudeBands + 1)) + longNumber;
			GLuint second = (GLuint)(first + longitudeBands + 1);

			Indices.push_back(first);
			Indices.push_back(second);
			Indices.push_back(first + 1);

			Indices.push_back(second);
			Indices.push_back(second + 1);
			Indices.push_back(first + 1);
		}
	}


	
	//vertices.clear(); indices.clear();
	//vertices = Vertices;
	//indices = Indices;

	_rModel.VertForm.clear();
	_rModel.vertexIndices.clear();

	_rModel.VertForm = Vertices;
	_rModel.vertexIndices = Indices;
		
	
}
