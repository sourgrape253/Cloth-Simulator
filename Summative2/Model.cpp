#include "Model.h"
#include "Utils.h"
#include "GameScene.h"


Model::Model()
{

}

/*
* Function - Model()
* Model constructor which sets its position, tecture as well as rotation and scale

*/
Model::Model(ModelType Shape, char* Filename, GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat X_Scale, GLfloat Y_Scale, GLfloat Z_Scale, glm::vec3 _Rotation)
{
	m_Shape = Shape;
	texFileName = Filename;
	_rscene = &GameScene::GetInstance();
	Rotation = _Rotation;

	if (m_Shape == CUBE || m_Shape == LIGHT)
	{
		SetCube(*this);
	}
	else if (m_Shape == TRIANGLE)
	{
		SetTriangle(*this);
	}
	else if (m_Shape == SQUARE)
	{
		SetSquare(*this);
	}
	else if (m_Shape == PYRAMID)
	{
		SetPyramid(*this);
	}
	else if (m_Shape == SPHERE)
	{
		ModelSpeed = glm::vec3(0.5f, 0.5f, 0.5f);
		setSphereData(VertForm, vertexIndices, *this);
	}

	m_ModelPosition = glm::vec3(xPos, yPos, zPos);
	m_Scale = glm::vec3(X_Scale, Y_Scale, Z_Scale);
	Init();
}

/*
* Function - Model()
* Model destructor

*/
Model::~Model()
{

}

/*
* Function - Render()
* Renders the model by passing in vertices and indices to the shaders

*/
void
Model::Render(GLuint program)
{
	// Draw our first triangle
	glUseProgram(program);

	/*glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 0.0f);
	glEnd();*/

	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(vao);

	GLfloat currentTime = glutGet(GLUT_ELAPSED_TIME); // get current time
	currentTime = currentTime / 1000; // convert milliseconds to seconds

	GLint currentTimeLocation = glGetUniformLocation(program, "currentTime"); // get uniform location from program
	glUniform1f(currentTimeLocation, currentTime); // set value
	//printf("currenttime, %f \n", currentTime); // Debug commands.

	GLint LightPosLoc = glGetUniformLocation(program, "lightPos"); // get uniform location from program
	glUniform3f(LightPosLoc,
		_rscene->sceneLight->lightPos.x,
		_rscene->sceneLight->lightPos.y,
		_rscene->sceneLight->lightPos.z); // set value

	GLint lightColorLoc = glGetUniformLocation(program, "lightColor"); // get uniform location from program
	glUniform3f(lightColorLoc,
		_rscene->sceneLight->lightColor.x,
		_rscene->sceneLight->lightColor.y,
		_rscene->sceneLight->lightColor.z); // set value

	GLint lightDirLoc = glGetUniformLocation(program, "lightDir"); // get uniform location from program
	glUniform3f(lightDirLoc,
		_rscene->sceneLight->lightDir.x,
		_rscene->sceneLight->lightDir.y,
		_rscene->sceneLight->lightDir.z); // set value

	GLint cameraPosLoc = glGetUniformLocation(program, "cameraPos"); // get uniform location from program
	glUniform3f(cameraPosLoc,
		_rscene->sceneCamera->m_CameraPosition.x,
		_rscene->sceneCamera->m_CameraPosition.y,
		_rscene->sceneCamera->m_CameraPosition.z); // set value

	GLint modelLoc = glGetUniformLocation(program, "model");
	GLint viewLoc = glGetUniformLocation(program, "view");
	GLint projLoc = glGetUniformLocation(program, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_rscene->view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(_rscene->projection));

	glDrawElements(GL_TRIANGLES, vertexIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

/*
* Function - MoveLightSource()
* Move the light source and model based on user input

*/
void
Model::MoveLightSource()
{
	if (m_Shape == LIGHT)
	{
		// forward
		if (_rscene->keyState[(unsigned char) 'u'] == BUTTON_DOWN)
		{
			m_ModelPosition -= ModelFront * ModelSpeed;
		}
		// Back
		if (_rscene->keyState[(unsigned char) 't'] == BUTTON_DOWN)
		{
			m_ModelPosition += ModelFront * ModelSpeed;
		}
		// Left
		if (_rscene->keyState[(unsigned char) 'g'] == BUTTON_DOWN)
		{
			m_ModelPosition -= glm::normalize(glm::cross(ModelFront, ModelUp)) * ModelSpeed;
		}
		//Right
		if (_rscene->keyState[(unsigned char) 'j'] == BUTTON_DOWN)
		{
			m_ModelPosition += glm::normalize(glm::cross(ModelFront, ModelUp)) * ModelSpeed;
		}
		//move up
		if (_rscene->keyState[(unsigned char) 'y'] == BUTTON_DOWN)
		{
			m_ModelPosition += ModelUp * ModelSpeed;
		}
		//move down
		if (_rscene->keyState[(unsigned char) 'h'] == BUTTON_DOWN)
		{
			m_ModelPosition -= ModelUp * ModelSpeed;
		}

		// set the light position equal to the objects position
		_rscene->sceneLight->SetLightPos(m_ModelPosition.x, m_ModelPosition.y, m_ModelPosition.z);
	}
}

/*
* Function - UpdateModel()
* Update model position, scale and rotation

*/
void
Model::UpdateModel()
{
	glm::mat4 _Model;

	_Model = glm::translate(_Model, m_ModelPosition);

	_Model = glm::scale(_Model, m_Scale);

	_Model = glm::rotate(_Model, Rotation.x/* * DEGTORAD*/, glm::vec3(1, 0, 0));
	//_Model = glm::rotate(_Model, Rotation.y /** DEGTORAD*/, glm::vec3(0, 1, 0));
	//_Model = glm::rotate(_Model, Rotation.z /** DEGTORAD*/, glm::vec3(0, 0, 1));
	

	model = _Model;
}

/*
* Function - Init()
* Initialise models with vertices and indices, prepare buffers

*/
void
Model::Init()
{
	if (m_Shape == SPHERE)
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, VertForm.size() * sizeof(VertexFormat),
			&VertForm[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(GLuint),
			&vertexIndices[0], GL_STATIC_DRAW);

		// Vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
			(GLvoid*)0);

		// Vertex Normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
			(GLvoid*)offsetof(VertexFormat, normal));

		// Vertex Texture Coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
			(GLvoid*)offsetof(VertexFormat, newTex));

		ApplyTexture();

		// Its always a good thing to unbind any buffer/ array to prevent strangebugs
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}


	else
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
			8 * sizeof(GLfloat), // size of the data
			(GLvoid*)0); // stride
		glEnableVertexAttribArray(0);

		//normalz
		glVertexAttribPointer(1, // tie vertex attrib from shader to OpenGL)
			3, // sending 3 vertices
			GL_FLOAT, //type of data sent
			GL_FALSE, // is data normalised
			8 * sizeof(GLfloat), // size of the data
			(GLvoid*)(3 * sizeof(GLfloat))); // stride
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, // tie vertex attrib from shader to OpenGL)
			2, // sending 2 vertices
			GL_FLOAT, //type of data sent
			GL_FALSE, // is data normalised
			8 * sizeof(GLfloat), // size of the data
			(GLvoid*)(6 * sizeof(GLfloat))); // stride
		glEnableVertexAttribArray(2);

		ApplyTexture();

		// Its always a good thing to unbind any buffer/ array to prevent strangebugs
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}
}

/*
* Function - ApplyTexture()
* Apply textures to models

*/
void
Model::ApplyTexture()
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image(texFileName, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}
