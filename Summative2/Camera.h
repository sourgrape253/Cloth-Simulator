#pragma once

#include "GameScene.h"
#include <iostream>

#define BUTTON_UP 0
#define BUTTON_DOWN 1

class Camera
{
public:
	Camera(GLfloat _Xpos, GLfloat _Ypos, GLfloat _Zpos, glm::vec3 _Speed);
	~Camera();

	// Camere member variables
	glm::vec3 m_CameraPosition;
	glm::vec3 m_CameraFront;
	glm::vec3 m_CamUp;
	glm::vec3 m_CamSpeed;

	// Matrixes
	glm::mat4 Projectionmatrix;
	glm::mat4 ViewMatrix;

	// cam positions
	GLfloat CamPos_X;
	GLfloat CamPos_Y;
	GLfloat CamPos_Z;

	void MoveCamera();
	void SetCameraFront(glm::vec3 _FrotVec);

	unsigned char keyState[255];

private:

};
