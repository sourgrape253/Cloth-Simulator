#pragma once

#include "GameScene.h"
#include "Cloth.h"

class Cloth;
class GameScene;

class Physics
{
public:
	Physics(int _FixedDeltaTime, int _RemainingDeltaTime, int _ConstraintAccuracy, Cloth* _Cloth);
	~Physics();

	void UpdatePhysics();

public:

	GLfloat m_GravityScalar;
	GLfloat m_PreviousTime;
	GLfloat m_CurrentTime;
	int m_FixedDeltaTime;
	GLfloat m_FixedDeltaTimeSecs;
	int m_RemainingDeltaTime;
	int m_ConstraintAccuracy;

	Cloth* m_Cloth;

	GameScene* _rscene;
};
