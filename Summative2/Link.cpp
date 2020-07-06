#include "Link.h"

/*
* Function - Link()
* Link constructor

*/
Link::Link(Particle* _P1, Particle* _P2, GLfloat _RestDist, GLfloat _linkStiff, GLfloat _LinkSensitivity)
{
	_rscene = &GameScene::GetInstance();

	m_Particle1 = _P1;
	m_Particle2 = _P2;
	m_RestDistance = _RestDist;
	m_Stiffness = _linkStiff;
	m_TearSensitivity = _LinkSensitivity;
}


/*
* Function - UpdateLink()
* Calculates the distances between links and tries to maintain the cloths resting distance
* Also checks if the cloth should be torn based on distance between these links.

*/
void
Link::LinkConstraints()
{
	GLfloat Distance = glm::distance(m_Particle1->m_CurrentPosition, m_Particle2->m_CurrentPosition);

	//GLfloat diff = (m_RestDistance * sqrt(2) - Distance) / Distance;

	// calculate dist along rest dist
	GLfloat diff = (m_RestDistance - Distance) / Distance;

	// if more than tear sensitivity tear cloth
	if (Distance > m_TearSensitivity)
	{
		m_Particle1->DetatchLink(this);
	}

	// inverse mass quantities
	GLfloat im1 = 1 / m_Particle1->m_Mass;
	GLfloat im2 = 1 / m_Particle2->m_Mass;

	GLfloat ScalarP1 = (im1 / (im1 + im2)) * m_Stiffness;
	GLfloat ScalarP2 = m_Stiffness - ScalarP1;

	// push and pull based on mass
	glm::vec3 Delta = m_Particle1->m_CurrentPosition - m_Particle2->m_CurrentPosition;

	m_Particle1->m_CurrentPosition += Delta * ScalarP1 * diff;
	m_Particle2->m_CurrentPosition -= Delta * ScalarP2 * diff;
}

/*
* Function - RenderLink()
* Renders the line between each particle(link) using the links specified color

*/
void
Link::RenderLink()
{
	// Draw our first triangle
	glUseProgram(_rscene->glColorProgram);


	// more to be passed in here "MVP"
	GLint mvpLoc = glGetUniformLocation(_rscene->glColorProgram, "mvp");

	glm::mat4 mvp = _rscene->projection * _rscene->view * model;
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

	GLint ColorLoc = glGetUniformLocation(_rscene->glColorProgram, "Color");

	glm::vec3 Color = m_Color;
	glUniform3f(ColorLoc,
		m_Color.x,
		m_Color.y,
		m_Color.z); // set value

	GLint PosLoc = glGetUniformLocation(_rscene->glColorProgram, "position");

	//glm::vec3 Position = ;
	//glUniform3f(ColorLoc,
	//	m_Color.x,
	//	m_Color.y,
	//	m_Color.z); // set value

	glBegin(GL_LINES);
	glVertex3f(m_Particle1->m_CurrentPosition.x, m_Particle1->m_CurrentPosition.y, m_Particle1->m_CurrentPosition.z);
	glVertex3f(m_Particle2->m_CurrentPosition.x, m_Particle2->m_CurrentPosition.y, m_Particle2->m_CurrentPosition.z);
	glEnd();


}

/*
* Function - SetLinkColor()
* Sets the color value of the specified link

*/
void 
Link::SetLinkColor(glm::vec3 _Color)
{
	m_Color = _Color;
}

