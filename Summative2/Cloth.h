#pragma once

#include "GameScene.h"
#include "Particle.h"
#include "Link.h"

class Particle;
class Link;
class Physics;

class Cloth
{
public:
	Cloth(glm::vec3 _StartPos, int _Width, int _Height, /*Physics* _Physics,*/ GLfloat _RestDist, GLfloat _ClothStiff, GLfloat _ClothSensitivity, GLint _Hooks);
	Cloth() {}
	~Cloth();

	void CreateCloth(int _Links);


public:
	std::vector<Particle*> m_Cloth_Parts;
	std::vector<Particle*> m_Pinned_Particles;
	glm::vec3 m_Position;
	glm::vec3 m_StartPos;

	int m_ClothWidth;
	int m_ClothHeight;
	Physics* m_ClothPhysics;

	GLfloat m_Cloth_Resting_Distance;
	GLfloat m_Cloth_Stiffness;
	GLfloat m_Cloth_Tear_Sensitivity;
	GLint m_NumHooks;
	GLint m_NumberLinks;
};

