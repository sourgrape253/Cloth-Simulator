#include "Physics.h"

/*
* Function - Physics()
* Physics constructor to set up the physics within the world

*/
Physics::Physics(int _FixedDeltaTime, int _RemainingDeltaTime, int _ConstraintAccuracy, Cloth* _Cloth)
{
	_rscene = &GameScene::GetInstance();

	m_FixedDeltaTime = _FixedDeltaTime;
	m_FixedDeltaTimeSecs = (GLfloat)m_FixedDeltaTime / 1000;
	m_RemainingDeltaTime = _RemainingDeltaTime;
	m_ConstraintAccuracy = _ConstraintAccuracy;

	m_CurrentTime = glutGet(GLUT_ELAPSED_TIME); // get current time
	m_PreviousTime = m_CurrentTime;
	m_Cloth = _Cloth;

	m_GravityScalar = -9.8f;
}

/*
* Function - ~Physics()
* Physics constructor to set up the physics within the world

*/
Physics::~Physics()
{

}

/*
* Function - UpdatePhysics()
* Updates the 

*/
void
Physics::UpdatePhysics()
{
	m_CurrentTime = glutGet(GLUT_ELAPSED_TIME); // get current time
												//currentTime = currentTime / 1000; // convert milliseconds to seconds

	GLfloat DeltaTime = m_CurrentTime - m_PreviousTime;

	m_PreviousTime = m_CurrentTime;

	int _TimeStepAMT = (int)((GLfloat)(DeltaTime + m_RemainingDeltaTime) / (float)m_FixedDeltaTime);

	// limit the time step to prevent freezing
	_TimeStepAMT = glm::min(_TimeStepAMT, 5);

	// store remaining time left for next frame
	m_RemainingDeltaTime = (int)DeltaTime - (_TimeStepAMT*m_FixedDeltaTime);

	// UpdatePositions
	for (int i = 0; i < m_Cloth->m_Cloth_Parts.size(); i++)
	{
		m_Cloth->m_Cloth_Parts[i]->UpdatePhysics(m_FixedDeltaTimeSecs);

		// floor check
		if (m_Cloth->m_Cloth_Parts[i]->m_CurrentPosition.y <= -100)
		{
			m_Cloth->m_Cloth_Parts[i]->m_CurrentPosition.y = -100;
			m_Cloth->m_Cloth_Parts[i]->m_IsGrounded = true;
		}
		else
		{
			m_Cloth->m_Cloth_Parts[i]->m_IsGrounded = false;
		}

		// randcolors
		if (_rscene->b_RainbowCloth)
		{
			if (_rscene->ColorRandTime <= 0)
			{
				m_Cloth->m_Cloth_Parts[i]->UpdateColors();
			}
		}
	}

	if (_rscene->ColorRandTime <= 0)
	{
		_rscene->ColorRandTime = _rscene->ConstColorTime;
	}

	
		for (unsigned int i = 0; i < m_ConstraintAccuracy; i++)
		{
			for (int j = 0; j < m_Cloth->m_Cloth_Parts.size(); j++)
			{
				m_Cloth->m_Cloth_Parts[j]->SolveCOnstraints();

				// sphere collision
				if (_rscene->SphereActive)
				{
					m_Cloth->m_Cloth_Parts[j]->m_CurrentPosition += m_Cloth->m_Cloth_Parts[j]->SphereConstraint(m_Cloth->m_Cloth_Parts[j]->m_CurrentPosition, _rscene->Sphere->m_ModelPosition, 30.0f);

				}
			}
		}
	
}


