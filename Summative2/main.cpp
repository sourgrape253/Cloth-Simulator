#include <iostream>
#include "GameScene.h"

#define BUTTON_UP 0
#define BUTTON_DOWN 1

#define MOUSE_DOWN 0
#define MOUSE_UP 1

// Mouse
#define MOUSE_LEFT 0
#define MOUSE_MIDDLE 1
#define MOUSE_RIGHT 2
unsigned char mouseState[3];
GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool firstMouse = true;

GameScene* rGame;
Camera* _SceneCamera;

// Picking
glm::vec3 g_RayDirection;
float g_MouseX;
float g_MouseY;

/*
* Function - Keyboard()
* Set keyboard state to key down and pass in key pressed

*/
void Keyboard(unsigned char key, int x, int y)
{
	rGame->keyState[key] = BUTTON_DOWN;
	_SceneCamera->keyState[key] = BUTTON_DOWN;
}

/*
* Function - Keyboard_up()
* Set keyboard state to up and pass in the key released

*/
void Keyboard_up(unsigned char key, int x, int y)
{
	rGame->keyState[key] = BUTTON_UP;
	_SceneCamera->keyState[key] = BUTTON_UP;

}

/*
* Function - UpdateMousePicking()
* Checks for user clicks and processes wether the mouse collided with any objects

*/
void UpdateMousePicking()
{
	// screen Pos
	glm::vec2 normalizedScreenPos = glm::vec2(g_MouseX, g_MouseY);

	// screen pos to proj space
	glm::vec4 clipCoords = glm::vec4(normalizedScreenPos.x, normalizedScreenPos.y, -1.0f, 1.0f);

	//Proj space to eye space
	glm::mat4 invProjMat = glm::inverse(rGame->sceneCamera->Projectionmatrix);

	glm::vec4 eyeCoords = invProjMat * clipCoords;
	eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);

	// eyespace to world space
	glm::mat4 invViewMat = glm::inverse(rGame->view);
	glm::vec4 RayWorld = invViewMat * eyeCoords;
	g_RayDirection = glm::normalize(glm::vec3(RayWorld));

	rGame->_RayPickDir = g_RayDirection;
}


/*
* Function - mouse()
* Check the current state of the mouse

*/
void mouse(int button, int button_state, int x, int y)
{
#define state ((button_state == GLUT_DOWN) ? MOUSE_DOWN : MOUSE_UP);
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			mouseState[MOUSE_LEFT] = state;
			if (button_state == MOUSE_DOWN)
				{
					for (int j = 0; j < rGame->CurtainCloth->m_Cloth_Parts.size(); j++)
					{
						rGame->CurtainCloth->m_Cloth_Parts[j]->UpdateInteractions(g_RayDirection, _SceneCamera->m_CameraPosition);	
					}

					rGame->Particle_Dragging = true;
				}
				else 
				{
					rGame->Particle_Dragging = false;
					rGame->m_PickedParticles.clear();
				}

			break;

		case GLUT_MIDDLE_BUTTON:
			mouseState[MOUSE_MIDDLE] = state;
			break;

		case GLUT_RIGHT_BUTTON:
			mouseState[MOUSE_RIGHT] = state; 

			if (button_state == MOUSE_DOWN)
			{
				for (int j = 0; j < rGame->CurtainCloth->m_Cloth_Parts.size(); j++)
				{
					rGame->CurtainCloth->m_Cloth_Parts[j]->TearCloth(g_RayDirection, _SceneCamera->m_CameraPosition);
				}

				rGame->Particle_Dragging = true;
			}
			else
			{
				rGame->Particle_Dragging = false;
				rGame->m_PickedParticles.clear();
			}
			break;

	default:
		break;
	}
}

/*
* Function - UpdateMouseWhilstClicked()
* Process mouse position when clicked

*/
void UpdateMouseWhilstClicked(int x, int y)
{
	// Picking
	g_MouseX = (2.0f * x) / (float)WIDTH - 1.0f;
	g_MouseY = 1.0f - (2.0f * y) / (float)HEIGHT;
}


/*
* Function - mousePassiveMove()
* Process the current mouse position

*/
void mousePassiveMove(int x, int y)
{
	// Picking
	g_MouseX = (2.0f * x) / (float)WIDTH - 1.0f;
	g_MouseY = 1.0f - (2.0f * y) / (float)HEIGHT;

	if (firstMouse)
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
	}

	if (x > WIDTH - 100.0f || x < 100 || y > HEIGHT - 100.0f || y < 100) {
		glutWarpPointer(400, 300);
		lastX = 400;
		lastY = 300;
	}

	GLfloat xoffset = x - lastX;
	GLfloat yoffset = lastY - y;	// reversed since y-co ords go from bottom to left
	
	lastX = x;
	lastY = y;

	GLfloat sensitivity = 0.1;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesnt get flipped
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(yaw * DEGTORAD) * cos(pitch * DEGTORAD);
	front.y = sin(pitch * DEGTORAD);
	front.z = sin(yaw * DEGTORAD) * cos(pitch * DEGTORAD);
	_SceneCamera->SetCameraFront(glm::normalize(front));
}

/*
* Function - SpecialInput()
* Process special inputs (arrow keys)

*/
void SpecialInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		//std::cout << "KeyUp" << std::endl;
		if (rGame->Selected_Attribute == CLOTHSCALE)
		{
			rGame->UpdateHeight(1);
		}
		if (rGame->Selected_Attribute == HOOKSIZE)
		{
			rGame->UpdateHooks(1);
		}
		if (rGame->Selected_Attribute == MOVEWIND)
		{
			rGame->MoveWind(1, false);
		}

		
		break;

	case GLUT_KEY_DOWN:
		//std::cout << "KeyDown" << std::endl;
		if (rGame->Selected_Attribute == CLOTHSCALE)
		{
			rGame->UpdateHeight(-1);
		}
		if (rGame->Selected_Attribute == HOOKSIZE)
		{
			rGame->UpdateHooks(-1);
		}
		if (rGame->Selected_Attribute == MOVEWIND)
		{
			rGame->MoveWind(-1, false);
		}

		break;

	case GLUT_KEY_LEFT:
		//std::cout << "Keyleft" << std::endl;
		if (rGame->Selected_Attribute == CLOTHSCALE)
		{
			rGame->UpdateWidth(-1);
		}
		if (rGame->Selected_Attribute == HOOKSIZE)
		{
			rGame->UpdateHooks(-1);
		}
		if (rGame->Selected_Attribute == MOVEHOOKS)
		{
			rGame->MoveHooks(false);
		}
		if (rGame->Selected_Attribute == CLOTHSTRUCTURE)
		{
			rGame->UpdateClothStructure();
		}
		if (rGame->Selected_Attribute == MOVEWIND)
		{
			rGame->MoveWind(-1, true);
		}
		if (rGame->Selected_Attribute == WINDSPEED)
		{
			rGame->UpdateWindSpeed(-1);
		}

		break;

	case GLUT_KEY_RIGHT:
		//std::cout << "Keyright" << std::endl;
		if (rGame->Selected_Attribute == CLOTHSCALE)
		{
			rGame->UpdateWidth(1);
		}
		if (rGame->Selected_Attribute == HOOKSIZE)
		{
			rGame->UpdateHooks(1);
		}
		if (rGame->Selected_Attribute == MOVEHOOKS)
		{
			rGame->MoveHooks(true);
		}
		if (rGame->Selected_Attribute == CLOTHSTRUCTURE)
		{
			rGame->UpdateClothStructure();
		}
		if (rGame->Selected_Attribute == MOVEWIND)
		{
			rGame->MoveWind(1, true);
		}
		if (rGame->Selected_Attribute == WINDSPEED)
		{
			rGame->UpdateWindSpeed(1);
		}

		break;

	default:
		
		break;
	}

	std::cout << rGame->CurrentlySelecting << std::endl;
}

/*
* Function - init()
* Main initialise function which calls the Game world initialise to create the game

*/
void init()
{
	rGame->InitGameWorld();
}

/*
* Function - render()
* Main render loop which calls the render function to render game objects

*/
void render()
{
	rGame->RenderGameWorld();
}

/*
* Function - update()
* Main update loop which calls the game world update and processes all actions/entities

*/
void update()
{
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(Keyboard_up);

	rGame->UpdateCamera();
	rGame->UpdateGameWorld();
	UpdateMousePicking();

}

/*
* Function - main()
* Main loop to create and run the programme

*/
int main(int argc, char **argv)
{
	
	glutInit(&argc, argv);
	// make sure to include GLUT_MULTISAMPLE for anti alisaing
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Cloth Curtain Thingy");

	glewInit();

	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);

	//Enable anti aliasing
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glEnable(GL_MULTISAMPLE);
	glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);

	// Enable back face culling
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);

	rGame = &GameScene::GetInstance();

	_SceneCamera = rGame->sceneCamera;

	init();
	glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);

	glClearColor(1.0, 0.0, 1.0, 1.0); // clear red

	// Mouse
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mousePassiveMove);
	glutMotionFunc(UpdateMouseWhilstClicked);

	// special
	glutSpecialFunc(SpecialInput);

	// register callbacks
	glutDisplayFunc(render);
	glutIdleFunc(update);
	glutMainLoop();

	return (0);
}
