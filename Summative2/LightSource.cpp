#include "Model.h"
#include "Utils.h"
#include "GameScene.h"

/*
* Function - Light()
* Create a light with position, direction and color

*/
Light::Light(glm::vec3 _LightPos, glm::vec3 _LightColor, glm::vec3 _LightDir)
{
	_rscene = &GameScene::GetInstance();
	SetLightPos(_LightPos.x, _LightPos.y, _LightPos.z);
	lightColor = glm::vec3(_LightColor.x, _LightColor.y, _LightColor.z);
	lightDir = glm::vec3(_LightDir.x, _LightDir.y, _LightDir.z);
}

/*
* Function - ~Light()
* Destroy light source

*/
Light::~Light()
{

}

/*
* Function - SetLightPos()
* Set the position of the light

*/
void
Light::SetLightPos(GLfloat x_Pos, GLfloat y_Pos, GLfloat z_Pos)
{
	lightPos = glm::vec3(x_Pos, y_Pos, z_Pos);
}

/*
* Function - GetLightPos()
* Get the position of the light

*/
glm::vec3 
Light::GetLightPos()
{
	return lightPos;
}

/*
* Function - SetLightColor()
* Set the color of the light

*/
void
Light::SetLightColor(GLfloat R, GLfloat G, GLfloat B)
{
	lightColor = glm::vec3(R, G, B);
}

/*
* Function - GetLightColor()
* Get the color of the light

*/
glm::vec3 
Light::GetLightColor()
{
	return lightColor;
}

/*
* Function - SetLightDirection()
* Set the direction of the light

*/
void
Light::SetLightDirection(GLfloat x, GLfloat y, GLfloat z)
{
	lightDir = glm::vec3(x, y, z);
}

/*
* Function - GetLightDirection()
* Get the direction of the light

*/
glm::vec3
Light::GetLightDirection()
{
	return lightDir;
}







