//#include "Model.h"
#include "Utils.h"
#include "GameScene.h"
#include "Skybox.h"

/*
* Function - SkyBox()
* Skybox default constructor

*/
SkyBox::SkyBox()
{

}

/*
* Function - SkyBox()
* Create a skybox cube to surround the gameworld (pass in 6 different textures for the box)

*/
SkyBox::SkyBox(ModelType Shape, char* Right, char* Left, char* Top, char* Bottom, char* Back, char* Front, GLfloat xPos, GLfloat yPos, GLfloat zPos)
{
	textures_faces.push_back(Right);
	textures_faces.push_back(Left);
	textures_faces.push_back(Top);
	textures_faces.push_back(Bottom);
	textures_faces.push_back(Back);
	textures_faces.push_back(Front);

	_rscene = &GameScene::GetInstance();

	SetSkyBox(*this);

	m_ModelPosition = glm::vec3(xPos, yPos, zPos);
}

/*
* Function - ~SkyBox()
* Skybox default destructor

*/
SkyBox::~SkyBox()
{

}

/*
* Function - ~SkyBox()
* Skybox default destructor

*/
void
SkyBox::RenderSkybox(GLuint program)
{
	glUseProgram(program);
	glBindVertexArray(vao);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(program, "cubeSampler"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	

	glm::mat4 mvp;
	mvp = _rscene->sceneCamera->Projectionmatrix * _rscene->sceneCamera->ViewMatrix * world;
	glUniformMatrix4fv(glGetUniformLocation(program, "mvp"), 1, GL_FALSE, glm::value_ptr(mvp));

	GLint CameraPosLoc = glGetUniformLocation(program, "cameraPos");
	glUniform3f(CameraPosLoc, _rscene->sceneCamera->m_CameraPosition.x, _rscene->sceneCamera->m_CameraPosition.y,
		_rscene->sceneCamera->m_CameraPosition.z);


	glDrawElements(GL_TRIANGLES, this->vertexIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

/*
* Function - UpdateModel()
* Update skybox position and scaling

*/
void
SkyBox::UpdateModel()
{
	world = glm::mat4();

	world = glm::translate(world, glm::vec3(0.0f, 0.0f, 0.0f));
	world = glm::scale(world, glm::vec3(3000.0f, 3000.0f, 3000.0f));
}

/*
* Function - Init()
* Initialise skybox entity

*/
void
SkyBox::Init()
{
	// VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // bind to context
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(GLuint) * vertices.size(), // GPU needs to know how much memory needs to be allocated
		vertices.data(), // copy data to GPU
		GL_STATIC_DRAW); // How to use the buffer - Buffer is created and modified once
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// **EBO
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		vertexIndices.size() * sizeof(GLuint),
		vertexIndices.data(),
		GL_STATIC_DRAW);

	glVertexAttribPointer(0, // tie vertex attrib from shader to OpenGL)
		3, // sending 3 vertices
		GL_FLOAT, //type of data sent
		GL_FALSE, // is data normalised
		3 * sizeof(GLfloat), // size of the data
		(GLvoid*)0); // stride
	glEnableVertexAttribArray(0);

	ApplyTexture();

	// Its always a good thing to unbind any buffer/ array to prevent strangebugs
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


/*
* Function - ApplyTexture()
* Apply 6 textures onto the skybox

*/
void
SkyBox::ApplyTexture()
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	
	// added for skybox textures
	int width, height;
	unsigned char* image;
	for (GLuint i = 0; i < textures_faces.size(); i++)
	{
		image = SOIL_load_image(textures_faces[i], &width, &height, 0, SOIL_LOAD_RGB);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
