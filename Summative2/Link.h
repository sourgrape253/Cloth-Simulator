#pragma once

#include "GameScene.h"
#include"Particle.h"
#include "Cloth.h"

class Particle;
class Cloth;

class Link
{
public:
	
	~Link();

	Link(Particle* _P1, Particle* _P2, GLfloat _RestDist, GLfloat _linkStiff, GLfloat _LinkSensitivity);

	void LinkConstraints();
	void RenderLink();
	void Init_Shader();
	void SetLinkColor(glm::vec3 _Color);

public:
	GLfloat m_RestDistance;
	GLfloat m_Stiffness;
	GLfloat m_TearSensitivity;

	Particle* m_Particle1;
	Particle* m_Particle2;

	GameScene* _rscene;

	glm::mat4 model;
	glm::vec3 m_Color = glm::vec3 (1.0f, 0.0f, 0.0f);
};


