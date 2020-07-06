#include "Camera.h"

/*
* Function - Camera()
* Creates a new camera with position and speed
* called when the gamescene is created

*/
Camera::Camera(GLfloat _Xpos, GLfloat _Ypos, GLfloat _Zpos, glm::vec3 _Speed)
{
	m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	m_CamUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_CameraPosition = glm::vec3(_Xpos, _Ypos, _Zpos);;
	m_CamSpeed = _Speed;
}

/*
* Function - ~Camera()
* Destroys the scene camera 

*/
Camera::~Camera()
{


}

/*
* Function - MoveCamera()
* takes in user input to Move the camera within the scene

*/
void
Camera::MoveCamera()
{
	if (keyState[(unsigned char) 'w'] == BUTTON_DOWN)
	{
		m_CameraPosition +=m_CameraFront * m_CamSpeed;
	}
	// Back
	if (keyState[(unsigned char) 's'] == BUTTON_DOWN)
	{
		m_CameraPosition -= m_CameraFront * m_CamSpeed;
	}
	// Left
	if (keyState[(unsigned char) 'a'] == BUTTON_DOWN)
	{
		m_CameraPosition -= glm::normalize(glm::cross(m_CameraFront, m_CamUp)) * m_CamSpeed;
	}
	//Right
	if (keyState[(unsigned char) 'd'] == BUTTON_DOWN)
	{
		m_CameraPosition += glm::normalize(glm::cross(m_CameraFront, m_CamUp)) * m_CamSpeed;
	}
	//move up
	if (keyState[(unsigned char) 'q'] == BUTTON_DOWN)
	{
		m_CameraPosition += m_CamUp * m_CamSpeed;
	}
	//move down
	if (keyState[(unsigned char) 'e'] == BUTTON_DOWN)
	{
		m_CameraPosition -= m_CamUp * m_CamSpeed;
	}
}

/*
* Function - SetCameraFront()
* Used to set the front of the camera

*/
void 
Camera::SetCameraFront(glm::vec3 _FrotVec)
{
	m_CameraFront = _FrotVec;
}
