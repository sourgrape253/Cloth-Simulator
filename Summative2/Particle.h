#pragma once

#include "GameScene.h"
#include "Link.h"
#include "Physics.h"
#include "Cloth.h"

class Link;
class Cloth;
class Physics;
class GameScene;

class Particle
{
public:
	~Particle();

	Particle(glm::vec3 _Pos, GLfloat _Mass, bool _Pinned/*, Physics* _Physics*/);
	void UpdatePhysics(GLfloat _Timestep);
	bool UpdateInteractions(glm::vec3 _RayDir, glm::vec3 _CamPos);
	bool TearCloth(glm::vec3 _RayDir, glm::vec3 _CamPos);
	void Render();
	void SolveCOnstraints();

	void LinkTo(Particle* _Point, GLfloat _RestDist, GLfloat _Stiffness);
	void LinkTo(Particle* _Point, GLfloat _RestDist, GLfloat _Stiffness, GLfloat _TearDIstance);

	void DetatchLink(Link* _LinkToDestroy);
	void ApplyForce(glm::vec3 _Force);
	void PinParticle(glm::vec3 _PinPos);

	void FollowMouse(glm::vec3 _CamPos, glm::vec3 _Ray);

	void RandomiseParticleWind();

	void UpdateColors();

	glm::vec3 SphereConstraint(glm::vec3 _Position, glm::vec3 _Center, GLfloat _Radius);
	glm::vec3 PyramidConstraint(glm::vec3 _Position, glm::vec3 _Center, GLfloat _Height);

public:

	GameScene* _rScene;
	glm::vec3 m_PreviousPosition;
	glm::vec3 m_CurrentPosition;
	glm::vec3 m_Acceleration;
	GLfloat m_Mass = 1;
	GLfloat m_Damping = 20;
	std::vector<Link*> Links;
	bool m_Pinned;
	glm::vec3 m_Pinned_Position;
	bool m_IsGrounded = false;
	Physics* m_CurrentPhysics;

	bool CycleUp_R = true;
	bool CycleUp_G = false;
	bool CycleUp_B = true;
};

