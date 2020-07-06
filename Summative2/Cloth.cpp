#include "Cloth.h"

/*
* Function - Cloth()
* Cloth Constructor

*/
Cloth::Cloth(glm::vec3 _StartPos, int _Width, int _Height, /*Physics* _Physics*/ GLfloat _RestDist, GLfloat _ClothStiff, GLfloat _ClothSensitivity, GLint _Hooks)
{
	m_Position = _StartPos;
	m_StartPos = _StartPos;

	m_ClothWidth = _Width;
	m_ClothHeight = _Height;

	m_Cloth_Resting_Distance = _RestDist;
	m_Cloth_Stiffness = _ClothStiff;
	m_Cloth_Tear_Sensitivity = _ClothSensitivity;

	m_NumHooks = _Hooks;

	//m_ClothPhysics = _Physics;

	//CreateCloth();
}

/*
* Function - ~Cloth()
* Cloth Destructor

*/
Cloth::~Cloth()
{

}

/*
* Function - CreateCloth()
* Used to create the particles and links of the cloth

*/
void
Cloth::CreateCloth(int _Links)
{
	GLint HookSeperationDist;
	m_NumberLinks = _Links;

	if (m_NumHooks > 0)
	{
		HookSeperationDist = floor(m_ClothWidth / m_NumHooks);
		//int multiplier = 1;
	}
	

	for (unsigned int y = 0; y < m_ClothHeight; y++)
	{
		for (unsigned int x = 0; x < m_ClothWidth; x++)
		{
			glm::vec3 _Pos;
			_Pos.x = m_Position.x + x * m_Cloth_Resting_Distance;
			_Pos.y = m_Position.y + y * m_Cloth_Resting_Distance;
			_Pos.z = m_Position.z /*+ y*/;

			GLfloat _Mass = 1.0f;

			Particle* _NewParticle = new Particle(_Pos, _Mass, false/*, m_ClothPhysics*/);


			
			if (x != 0)
			{
				_NewParticle->LinkTo(m_Cloth_Parts.back(), m_Cloth_Resting_Distance, m_Cloth_Stiffness);
			}


			if (y != 0)
			{
				// link 1
				_NewParticle->LinkTo(m_Cloth_Parts[(y - 1) * (m_ClothWidth)+x], m_Cloth_Resting_Distance, m_Cloth_Stiffness);

				// pythagoras for link 2
				GLfloat a = m_Cloth_Resting_Distance;
				GLfloat b = m_Cloth_Resting_Distance;
				GLfloat NewrestDist = sqrt((a * a) + (b * b));
				if (_Links == 2)
				{
					if (x < m_ClothWidth - 1)
					{
						// link 2
						_NewParticle->LinkTo(m_Cloth_Parts[(y - 1) * (m_ClothWidth)+x + 1], NewrestDist, m_Cloth_Stiffness);
					}
				}
				if (_Links == 3)
				{
					if (x < m_ClothWidth - 1)
					{
						// link 2
						_NewParticle->LinkTo(m_Cloth_Parts[(y - 1) * (m_ClothWidth)+x + 1], NewrestDist, m_Cloth_Stiffness);
					}
					if (x > 0)
					{
						// link 3
						_NewParticle->LinkTo(m_Cloth_Parts[(y - 1) * (m_ClothWidth)+x - 1], NewrestDist, m_Cloth_Stiffness);
					}
				}	
			}


			if (m_NumHooks == 2)
			{
				//pin top
				if (y == m_ClothHeight - 1 && x == 0)
				{
				_NewParticle->PinParticle(_NewParticle->m_CurrentPosition);
				}

				if (y == m_ClothHeight - 1 && x == m_ClothWidth - 1)
				{
				_NewParticle->PinParticle(_NewParticle->m_CurrentPosition);
				}

				m_Pinned_Particles.push_back(_NewParticle);
			}

			else if (x % HookSeperationDist == 0 && y == m_ClothHeight -1)
			{
				_NewParticle->PinParticle(_NewParticle->m_CurrentPosition);
				m_Pinned_Particles.push_back(_NewParticle);

			}

			// add to PointMass array  
			m_Cloth_Parts.push_back(_NewParticle);
		}
	}
}


