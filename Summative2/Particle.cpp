#include "Particle.h"


/*
* Function - Particle()
* Particle constructor

*/
Particle::Particle(glm::vec3 _Pos, GLfloat _Mass, bool _Pinned/*, Physics* _Physics*/)
{
	_rScene = &GameScene::GetInstance();

	// set current and previous position
	m_CurrentPosition = _Pos;
	m_PreviousPosition = _Pos;

	m_Mass = _Mass;
	m_Pinned = _Pinned;

	// set acceleration to 0
	m_Acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

	if (m_Pinned)
	{
		m_Pinned_Position = _Pos;
	}

	// set physics
	//m_CurrentPhysics = _Physics;
}

/*
* Function - ~Particle()
* Particle destructor

*/
Particle::~Particle()
{

}

/*
* Function - RandomiseParticleWind()
* Applys a wind force to particles within the wind box area

*/
void 
Particle::RandomiseParticleWind()
{
	int Rand = (rand() % 100);

	if (Rand < 50)
	{
		glm::vec3 WindPos = _rScene->RamdWindPos;

		GLfloat WindAreaSize_H = _rScene->UserSelectedHeight / 3;
		GLfloat WindAreaSize_W = _rScene->UserSelectedWidth / 3;

		if (this->m_CurrentPosition.x <= WindPos.x + WindAreaSize_W &&
			this->m_CurrentPosition.x >= WindPos.x - WindAreaSize_W &&
			this->m_CurrentPosition.y <= WindPos.y + WindAreaSize_H &&
			this->m_CurrentPosition.y >= WindPos.y - WindAreaSize_H)
		{
			glm::vec3 WindForce(0.0f, 0.0f, -(_rScene->UserSelectedWindSpeed));
			ApplyForce(WindForce);
		}
	}
}

/*
* Function - UpdatePhysics()
* Applys appropriate forces such as gravity and wind on particles
* uses verlet integration to calculate future positions of particles

*/
void
Particle::UpdatePhysics(GLfloat _Timestep)
{
	// Apply a wind force if the wind is active
	if (_rScene->WindActive)
	{
		int Rand = (rand() % 100);

		if (Rand < 50)
		{
			glm::vec3 WindPos = _rScene->WindBox->m_ModelPosition;

			GLfloat WindAreaSize_H = _rScene->UserSelectedHeight / 3;
			GLfloat WindAreaSize_W = _rScene->UserSelectedWidth / 3;

			if (this->m_CurrentPosition.x <= WindPos.x + WindAreaSize_W &&
				this->m_CurrentPosition.x >= WindPos.x - WindAreaSize_W &&
				this->m_CurrentPosition.y <= WindPos.y + WindAreaSize_H &&
				this->m_CurrentPosition.y >= WindPos.y - WindAreaSize_H)
			{
				glm::vec3 WindForce(0.0f, 0.0f, -(_rScene->UserSelectedWindSpeed));
				ApplyForce(WindForce);
			}
		}
	}

	if (_rScene->RandomWind)
	{
		RandomiseParticleWind();
	}

	if (m_IsGrounded == false)
	{
		// apply gravity
		glm::vec3 _GravityForce(0.0f, m_Mass * -50.0f, 1.0f);
		ApplyForce(_GravityForce);
	}
	

	// Calculate velocity
	glm::vec3 _Velocity;
	_Velocity = m_CurrentPosition - m_PreviousPosition;

	// dampen velocity
	_Velocity *= glm::vec3(0.99f, 0.99f, 0.99f);

	GLfloat _SquareTimeStep = _Timestep * _Timestep;
	glm::vec3 _TimestepMultiplier(_SquareTimeStep, _SquareTimeStep, _SquareTimeStep);
	glm::vec3 _Half(0.5f, 0.5f, 0.5f);

	// Calculate future position using verlet integration
	glm::vec3 _FuturePos = m_CurrentPosition + _Velocity + _Half * m_Acceleration * _TimestepMultiplier;

	// reset previous position
	m_PreviousPosition = m_CurrentPosition;

	// set new position
	m_CurrentPosition = _FuturePos;

	// Reset Acceleration;
	m_Acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
}

/*
* Function - UpdateInteractions()
* Process mouse input to grab particles on the cloth

*/
bool
Particle::UpdateInteractions(glm::vec3 _RayDir, glm::vec3 _CamPos)
{
	GLfloat  Radius = 5.0f;
	_RayDir *= -1;

	glm::vec3 v = m_CurrentPosition - _CamPos;

	GLfloat a = glm::dot(_RayDir, _RayDir);
	GLfloat b = 2 * glm::dot(v, _RayDir);
	GLfloat c = glm::dot(v, v) - Radius * Radius;
	GLfloat d = b * b - 4 * a * c;

	

	if (d > 0)
	{
		GLfloat x1 = (-b - sqrt(d)) / 2;
		GLfloat x2 = (-b + sqrt(d)) / 2;

		if (x1 >= 0 && x2 >= 0)
		{
			if (Links.size() > 0)
			{
				//DetatchLink(Links[0]);
			}
			
			_rScene->m_PickedParticles.push_back(this);
			
			return true;

		}
		if (x1 < 0 && x2 >= 0)
		{
			if (Links.size() > 0)
			{
				//DetatchLink(Links[0]);
			}
			
			_rScene->m_PickedParticles.push_back(this);

			return true;
		}
		return false;

	}
	else if (d <= 0) 
	{
		return false;// no intersection

	}
	return true;
}

/*
* Function - TearCloth()
* Process mouse input to tear particle links on the cloth

*/
bool 
Particle::TearCloth(glm::vec3 _RayDir, glm::vec3 _CamPos)
{
	GLfloat  Radius = 20.0f;
	_RayDir *= -1;

	glm::vec3 v = m_CurrentPosition - _CamPos;

	GLfloat a = glm::dot(_RayDir, _RayDir);
	GLfloat b = 2 * glm::dot(v, _RayDir);
	GLfloat c = glm::dot(v, v) - Radius * Radius;
	GLfloat d = b * b - 4 * a * c;



	if (d > 0)
	{
		GLfloat x1 = (-b - sqrt(d)) / 2;
		GLfloat x2 = (-b + sqrt(d)) / 2;

		if (x1 >= 0 && x2 >= 0)
		{
			if (Links.size() > 0)
			{
				//DetatchLink(Links[0]);
			}

			_rScene->m_PickedParticles.push_back(this);

			return true;

		}
		if (x1 < 0 && x2 >= 0)
		{
			if (Links.size() > 0)
			{
				//DetatchLink(Links[0]);
			}

			_rScene->m_PickedParticles.push_back(this);

			return true;
		}
		return false;

	}
	else if (d <= 0)
	{
		return false;// no intersection

	}
	return true;
}

/*
* Function - Render()
* Render function called on each link to draw the lines between particles

*/
void
Particle::Render()
{
	for (unsigned int i = 0; i < Links.size(); i++)
	{
		if (Links.size() > 0)
		{
			Links[i]->RenderLink();
		}
	}
}

/*
* Function - SolveCOnstraints()
* Solves constraints on each particle and updates positions if the particles are not pinned

*/
void
Particle::SolveCOnstraints()
{
	// constraints are used to maintain the distances between particles
	for (unsigned int i = 0; i < Links.size(); i++)
	{
		Links[i]->LinkConstraints();
	}

	// Check if the particle is pinned
	if (m_Pinned == true)
	{
		m_CurrentPosition = m_Pinned_Position;
	}
}

/*
* Function - LinkTo()
* Creates a link between 2 particles

*/
void
Particle::LinkTo(Particle* _Point, GLfloat _RestDist, GLfloat _Stiffness)
{
	LinkTo(_Point, _RestDist, _Stiffness, 20.0f);
}

/*
* Function - LinkTo()
* Creates a link between 2 particles

*/
void
Particle::LinkTo(Particle* _Point, GLfloat _RestDist, GLfloat _Stiffness, GLfloat _TearDIstance)
{
	Link* _NewLink = new Link(this, _Point, _RestDist, _Stiffness, _TearDIstance);

	GLfloat Width = _rScene->CurtainCloth->m_ClothWidth;
	GLfloat Height = _rScene->CurtainCloth->m_ClothHeight;
	
	GLfloat Width_Index = Width / 5;
	GLfloat _ClothRestDist = _rScene->CurtainCloth->m_Cloth_Resting_Distance;

	GLfloat Range1 = _rScene->CurtainCloth->m_StartPos.x + Width_Index* _ClothRestDist;
	GLfloat Range2 = _rScene->CurtainCloth->m_StartPos.x + Width_Index * 2 * _ClothRestDist;
	GLfloat Range3 = _rScene->CurtainCloth->m_StartPos.x + Width_Index * 3 * _ClothRestDist;
	GLfloat Range4 = _rScene->CurtainCloth->m_StartPos.x + Width_Index * 4 * _ClothRestDist;
	GLfloat Range5 = _rScene->CurtainCloth->m_StartPos.x + Width_Index * 5 * _ClothRestDist;
	
	// Colors

	glm::vec3 LimeGreen = glm::vec3(0.5f, 1.0f, 0.0f);

	glm::vec3 Purple = glm::vec3(0.5f, 0.0f, 0.5f);

	glm::vec3 Orange = glm::vec3(1.0f, 0.5f, 0.0f);

	glm::vec3 Red = glm::vec3(1.0f, 0.0f, 0.0f);

	glm::vec3 Green = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 Blue = glm::vec3(0.0f, 0.0f, 1.0f);

	glm::vec3 LightBlue = glm::vec3(0.0f, 0.5f, 1.0f);

	glm::vec3 LightRed = glm::vec3(0.7f, 0.0f, 0.1f);

	glm::vec3 Gold = glm::vec3(1.0f, 0.843f, 0.1f);


	if (_Point->m_CurrentPosition.x < Range1)
	{
		_NewLink->SetLinkColor(Orange);
	}
	if (_Point->m_CurrentPosition.x > Range1 && _Point->m_CurrentPosition.x < Range2 )
	{
		_NewLink->SetLinkColor(LightRed);
	}
	if (_Point->m_CurrentPosition.x > Range2 && _Point->m_CurrentPosition.x < Range3)
	{
		_NewLink->SetLinkColor(Purple);
	}
	if (_Point->m_CurrentPosition.x > Range3 && _Point->m_CurrentPosition.x < Range4)
	{
		_NewLink->SetLinkColor(LimeGreen);
	}
	if (_Point->m_CurrentPosition.x > Range4)
	{
		_NewLink->SetLinkColor(LightBlue);
	}

	Links.push_back(_NewLink);
}

/*
* Function - UpdateColors()
* Updates the colors of the cloth each frame

*/
void 
Particle::UpdateColors()
{

	for (unsigned int i = 0; i < Links.size(); i++)
	{
		GLfloat Col_R = Links[i]->m_Color.x;
		GLfloat Col_G = Links[i]->m_Color.y;
		GLfloat Col_B = Links[i]->m_Color.z;

		if (CycleUp_R)
		{
			Col_R += 0.01;
		}
		else
		{
			Col_R -= 0.01;
		}

		if (CycleUp_G)
		{
			Col_G += 0.01;
		}
		else
		{
			Col_G -= 0.01;
		}

		if (CycleUp_B)
		{
			Col_B += 0.01;
		}
		else
		{
			Col_B -= 0.01;
		}
		

		if (Col_R <= 0 || Col_R >= 0.9)
		{
			//Col_R = 0.99;
			CycleUp_R = !CycleUp_R;
		}

		if (Col_G <= 0 || Col_G >= 0.9)
		{
			//Col_G = 0.01;
			CycleUp_G = !CycleUp_G;
		}

		if (Col_B <= 0 || Col_B >= 0.9)
		{
			//Col_B = 0.99;
			CycleUp_B = !CycleUp_B;
		}

		glm::vec3 NewColor = glm::vec3(Col_R, Col_G, Col_B);


		Links[i]->SetLinkColor(NewColor);
	}

	
}

/*
* Function - DetatchLink()
* Destroys a link between 2 particles

*/
void
Particle::DetatchLink(Link* _LinkToDestroy)
{
	for (unsigned int i = 0; i < Links.size(); i++)
	{
		if (Links[i] == _LinkToDestroy)
		{
			Links.erase(Links.begin() + i);
		}
	}
}

/*
* Function - ApplyForce()
* Adds a force to the acceleration of the specified particle

*/
void
Particle::ApplyForce(glm::vec3 _Force)
{
	m_Acceleration += _Force / m_Mass;
}

/*
* Function - PinParticle()
* Sets a particles bool value to pinned 

*/
void
Particle::PinParticle(glm::vec3 _PinPos)
{
	m_Pinned = true;
	m_Pinned_Position = _PinPos;
}

/*
* Function - FollowMouse()
* Grabbed particles follow the mouse position

*/
void	
Particle::FollowMouse(glm::vec3 _CamPos, glm::vec3 _Ray)
{
	GLfloat Distance = glm::distance(_CamPos, m_CurrentPosition);
	glm::vec3 NewPos = _CamPos + (_Ray * Distance);

	m_CurrentPosition = NewPos;
}

/*
* Function - SphereConstraint()
* Sphere collision which pushes particles away from the sphere

*/
glm::vec3
Particle::SphereConstraint(glm::vec3 _Position, glm::vec3 _Center, GLfloat _Radius)
{
	glm::vec3 delta = _Position - _Center;
	GLfloat distance = glm::length(delta);

	if (distance <= _Radius)
	{
		glm::vec3 Result = (_Radius - distance) * delta / distance;
		return Result;
	}
		
	return glm::vec3 (0.0f, 0.0f, 0.0f);
}


//**not working**
//supposed to make cloth collide with triangle
glm::vec3
Particle::PyramidConstraint(glm::vec3 _Position, glm::vec3 _Center, GLfloat _Height)
{
	glm::vec3 delta = _Position - _Center;

	GLfloat distance = glm::length(delta);

	
	// height = 20
	// width = 20


	if (distance < _Height + 10)
	{
		glm::vec3 Result = ((_Height + 10) - distance) * delta / distance;
		return Result;
	}

	return glm::vec3(0.0f, 0.0f, 0.0f);
}

