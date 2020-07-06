#include <ctime>

#include "GameScene.h"
#include "Model.h"
#include "Skybox.h"

GameScene* GameScene::s_pGameScene = 0;

Model* LightCube;


/*
* Function - GetInstance()
* Creates a singleton gameinstance and then returns this instance when called

*/
GameScene&
GameScene::GetInstance()
{
	if (s_pGameScene == 0)
	{
		s_pGameScene = new GameScene();
	}

	return (*s_pGameScene);
}

/*
* Function - GameScene()
* Create the gamescene and set up its camera

*/
GameScene::GameScene()
{
	// pass in position and speed of camera
	glm::vec3 Speed(5.0f, 5.0f, 5.0f);
	sceneCamera = new Camera(0.0f, 200.0f, 540.0f, Speed);
	Particle_Dragging = false;
	Selected_Attribute = CLOTHSCALE;

	std::srand(std::time(0)); // use current time as seed for random generator
}

/*
* Function - ~GameScene()
* GameScene destructor

*/
GameScene::~GameScene()
{

}

/*
* Function - InitGameWorld()
* Initialise the gamescene and all elements within the scene

*/
void
GameScene::InitGameWorld()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_FILL, GL_LINE
	
	// create new light source
	glm::vec3 Pos(0.0f, 200.0f, 460.0f);
	glm::vec3 Color(1.0f, 1.0f, 1.0f);
	glm::vec3 Dir(0.0f, 0.0f, 1.0f);
	sceneLight = new Light(Pos, Color, Dir);

	// set camera and light start pos for resetting the scene
	Camera_StartPos = sceneCamera->m_CameraPosition;
	Light_StartPos = sceneLight->lightPos;

	// Create programmes
	Init_Programmes();
	// Initialise shapes
	Init_Shapes();
	// Initialise Camera
	Init_Camera();
	// Initialise Skybox
	Init_Skybox();

	// Init cloth stuff
	ShapeStartPos = glm::vec3(-75.0f, 100.0f, 200.0f);

	Sphere = new Model(ModelType::SPHERE, "Assets/Images/metal.jpg", ShapeStartPos.x, ShapeStartPos.y, ShapeStartPos.z, 1.0f, 1.0f, 1.0f, glm::vec3(0, 0, 0));
	Pyramid = new Model(ModelType::PYRAMID, "Assets/Images/purple.jpg", sceneCamera->CamPos_X -75.0f, sceneCamera->CamPos_Y + 40.0f, sceneCamera->CamPos_Z, 20.0f, 20.0f, 20.0f, glm::vec3(0, 0, 0));
	WindBox = new Model(ModelType::CUBE, "Assets/Images/green.jpg", ShapeStartPos.x, ShapeStartPos.y, 10.0f, 5.0f, 5.0f, 5.0f, glm::vec3(0, 0, 0));
	Ground = new Model(ModelType::SQUARE, "Assets/Images/bottom.jpg", 0, -100, 0, 500.0f, 500.0f, 500.0f, glm::vec3(90, 0, 0));

	UserSelectedHeight = 50;
	UserSelectedWidth = 50;
	UserSelectedHooks = 4;
	UserSelectedLinks = 1;

	CurtainCloth = new Cloth(glm::vec3(-150.0f, 50.0f, 0.0f), UserSelectedWidth, UserSelectedHeight, 3.0f, 0.5f, 6.0f, UserSelectedHooks);
	ClothPhysics = new Physics(20, 0, 3, CurtainCloth);
	CurtainCloth->CreateCloth(UserSelectedLinks);

	// Text
	Detatch_Txt = new TextLabel("0. Detatch Hooks:", "Dependencies/fonts/Arial.ttf");
	Detatch_Txt->setPosition(glm::vec2(10.0f, 860.0f));
	Detatch_Txt->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
	Detatch_Txt->setScale(0.5f);
	TextLabelVec.push_back(Detatch_Txt);

	Height = new TextLabel("1. Height: ", "Dependencies/fonts/Arial.ttf");
	Height->setPosition(glm::vec2(10.0f, 830.0f));
	Height->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
	Height->setScale(0.5f);
	TextLabelVec.push_back(Height);

	Width = new TextLabel("1. Width: ", "Dependencies/fonts/Arial.ttf");
	Width->setPosition(glm::vec2(10.0f, 800.0f));
	Width->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
	Width->setScale(0.5f);
	TextLabelVec.push_back(Width);

	Hooks = new TextLabel("2. Number of Hooks: ", "Dependencies/fonts/Arial.ttf");
	Hooks->setPosition(glm::vec2(10.0f, 770.0f));
	Hooks->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
	Hooks->setScale(0.5f);
	TextLabelVec.push_back(Hooks);

	MoveHooks_Txt = new TextLabel("3. Move Hooks: ", "Dependencies/fonts/Arial.ttf");
	MoveHooks_Txt->setPosition(glm::vec2(10.0f, 740.0f));
	MoveHooks_Txt->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
	MoveHooks_Txt->setScale(0.5f);
	TextLabelVec.push_back(MoveHooks_Txt);

	ClothStructure_Txt = new TextLabel("4. Cloth Structure: Weak Links", "Dependencies/fonts/Arial.ttf");
	ClothStructure_Txt->setPosition(glm::vec2(10.0f, 710.0f));
	ClothStructure_Txt->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
	ClothStructure_Txt->setScale(0.5f);
	TextLabelVec.push_back(ClothStructure_Txt);

	MoveWind_Txt = new TextLabel("5. Move WindBox", "Dependencies/fonts/Arial.ttf");
	MoveWind_Txt->setPosition(glm::vec2(10.0f, 680.0f));
	MoveWind_Txt->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
	MoveWind_Txt->setScale(0.5f);
	TextLabelVec.push_back(MoveWind_Txt);

	WindSpeed = new TextLabel("6. Wind Speed: 500.0f", "Dependencies/fonts/Arial.ttf");
	WindSpeed->setPosition(glm::vec2(10.0f, 650.0f));
	WindSpeed->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
	WindSpeed->setScale(0.5f);
	TextLabelVec.push_back(WindSpeed);

	RandomiseWind = new TextLabel("7. Randomise Wind: Inactive", "Dependencies/fonts/Arial.ttf");
	RandomiseWind->setPosition(glm::vec2(10.0f, 620.0f));
	RandomiseWind->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
	RandomiseWind->setScale(0.5f);
	TextLabelVec.push_back(RandomiseWind);

	Colour_Txt = new TextLabel("8. Color : Set", "Dependencies/fonts/Arial.ttf");
	Colour_Txt->setPosition(glm::vec2(10.0f, 590.0f));
	Colour_Txt->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
	Colour_Txt->setScale(0.5f);

	SphereActivity = new TextLabel("9. Sphere: Active", "Dependencies/fonts/Arial.ttf");
	SphereActivity->setPosition(glm::vec2(10.0f, 560.0f));
	SphereActivity->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
	SphereActivity->setScale(0.5f);

	Instructions = new TextLabel("Use arrow keys and num pad to adjust cloth", "Dependencies/fonts/Arial.ttf");
	Instructions->setPosition(glm::vec2(10.0f, 80.0f));
	Instructions->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
	Instructions->setScale(0.5f);

	 Restart_Txt = new TextLabel("Press 'R' to restart simulation", "Dependencies/fonts/Arial.ttf");
	 Restart_Txt->setPosition(glm::vec2(10.0f, 50.0f));
	 Restart_Txt->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
	 Restart_Txt->setScale(0.5f);

	 Space_Txt = new TextLabel("Press spacebar to hide UI", "Dependencies/fonts/Arial.ttf");
	 Space_Txt->setPosition(glm::vec2(10.0f, 20.0f));
	 Space_Txt->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
	 Space_Txt->setScale(0.5f);
}

/*
* Function - Init_Programmes()
* Initialise all programmes used by the scene

*/
void
GameScene::Init_Programmes()
{
	// Create a shader loader
	ShaderLoader shaderLoader;

	glColorProgram = shaderLoader.CreateProgram("Assets/Shaders/Basic_Shaders/Color.vs", "Assets/Shaders/Basic_Shaders/Color.fs");
	// standard shader
	glRegular_program = shaderLoader.CreateProgram("VAO_Triangle.vs", "VAO_Triangle.fs");

	// fog model shader
	glprogram = shaderLoader.CreateProgram("Assets/Shaders/Model_Fog.vs", "Assets/Shaders/Model_Fog.fs");

	//glModelProgram = shaderLoader.CreateProgram("Assets/Shaders/Mesh.vs", "Assets/Shaders/Mesh.fs");

	// normal terrain
	//glTerrainProgram = shaderLoader.CreateProgram("Assets/Shaders/Terrain.vs", "Assets/Shaders/Terrain.fs");
	// Fog terrain
	//glTerrainProgram = shaderLoader.CreateProgram("Assets/Shaders/Terrain_Fog.vs", "Assets/Shaders/Terrain_Fog.fs");
	// skybox programme
	glSkyBoxProgram = shaderLoader.CreateProgram("Assets/Shaders/SkyBox.vs", "Assets/Shaders/SkyBox.fs");
	// geometry programme
	//glGeometryProgram = shaderLoader.CreateProgram("Assets/Shaders/Geometry.vs", "Assets/Shaders/Geometry.fs", "Assets/Shaders/Geometry.gs");
	// tesselation program
	/*glTesselationProgram = shaderLoader.CreateProgram("Assets/Shaders/TesselationShaders/Tesselation.vs",
														"Assets/Shaders/TesselationShaders/Tesselation.fs",
															"Assets/Shaders/TesselationShaders/TessQuad.tcs",
																"Assets/Shaders/TesselationShaders/TessQuad.tes");

	/*glTesselationProgram = shaderLoader.CreateProgram("Assets/Shaders/TesselationShaders/Tesselation.vs",
														"Assets/Shaders/TesselationShaders/Tesselation.fs",
															"Assets/Shaders/TesselationShaders/TessTri.tcs",
																"Assets/Shaders/TesselationShaders/TessTri.tes");*/
}

/*
* Function - Init_Shapes()
* Initialise all basic shapes within the scene

*/
void
GameScene::Init_Shapes()
{
	// Create square object
	Model Square(ModelType::SQUARE, "Images/Bigblue.jpg", 20.0f, 200.0f, 450.0f, 5.0f, 5.0f, 5.0f, glm::vec3(0, 0, 0));
	Models.push_back(Square);

	// Create Triangle object
	Model Triangle(ModelType::TRIANGLE, "Images/red.jpg", -20.0f, 200.0f, 450.0f, 5.0f, 5.0f, 5.0f, glm::vec3(0, 0, 0));
	Models.push_back(Triangle);

	// Create Cube object
	//Model Cube(ModelType::CUBE, "Images/green.jpg", 0.0f, 220.0f, 450.0f, 5.0f, 5.0f, 5.0f, glm::vec3(0, 0, 0));
	//Models.push_back(Cube);

	// create pyramid object
	//Model Pyramid(ModelType::PYRAMID, "Images/purple.jpg", 0.0f, 180.0f, 450.0f, 5.0f, 5.0f, 5.0f, glm::vec3(45 , 0, 0));
	//Models.push_back(Pyramid);

	// create a transparent water effect
	//Model Water(ModelType::SQUARE, "Images/water.png", 0.0f, 200.0f, 450.0f, 5.0f, 5.0f, 5.0f, glm::vec3(0, 0, 0));
	//Models.push_back(Water);

	// create a light source model to show its position
	LightCube = new Model(ModelType::LIGHT, "Images/gold.jpg", sceneLight->lightPos.x, sceneLight->lightPos.y, sceneLight->lightPos.z, 1.0f, 1.0f, 1.0f, glm::vec3(0, 0, 0));

	// Create Cube object
	//Model Cube2(ModelType::CUBE, "Images/Crate.jpg", -30.0f, 220.0f, 450.0f, 5.0f, 5.0f, 5.0f, glm::vec3(45, 0, 45));
	//Models.push_back(Cube2);
	//// Create Cube object
	//Model Cube3(ModelType::CUBE, "Images/face.png", 30.0f, 220.0f, 450.0f, 5.0f, 5.0f, 5.0f, glm::vec3(45, 0, 0));
	//Models.push_back(Cube3);
	//// Create Cube object
	//Model Cube4(ModelType::CUBE, "Images/cube.jpg", -30.0f, 180.0f, 450.0f, 5.0f, 5.0f, 5.0f, glm::vec3(45, 130, 0));
	//Models.push_back(Cube4);
	//// Create Cube object
	//Model Cube5(ModelType::CUBE, "Images/TNT.jpg", 30.0f, 180.0f, 450.0f, 5.0f, 5.0f, 5.0f, glm::vec3(130, 0, 45));
	//Models.push_back(Cube5);

	// Create Sphere object
	//Model Sphere(ModelType::SPHERE, "Images/cube.jpg", 0.0f, 220.0f, 450.0f, 5.0f, 5.0f, 5.0f, glm::vec3(130, 0, 45));
	//Models.push_back(Sphere);	

	
}

/*
* Function - Init_Camera()
* Initialise the scene camera created at the start of the scene

*/
void 
GameScene::Init_Camera()
{
	GLfloat width = 800;
	GLfloat height = 600;

	// new view for camera movement
	projection = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 10000.0f);

	sceneCamera->Projectionmatrix = projection;

	view = glm::lookAt(sceneCamera->m_CameraPosition,
		sceneCamera->m_CameraPosition + sceneCamera->m_CameraFront,
		sceneCamera->m_CamUp);

	sceneCamera->ViewMatrix = view;
}

void
GameScene::Init_Skybox()
{
	// Add SkyBox
	Game_SkyBox = new SkyBox(CUBE,
		"Assets/Images/right.jpg",
		"Assets/Images/left.jpg",
		"Assets/Images/top.jpg",
		"Assets/Images/bottom.jpg",
		"Assets/Images/back.jpg",
		"Assets/Images/front.jpg",
		0.0f, 0.0f, 0.0f);

	Game_SkyBox->Init();
}

/*
* Function - RenderGameWorld()
* Render all objects/entities within the gameworld

*/
void
GameScene::RenderGameWorld()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use blending here
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Render Shapes
	//for (unsigned int i = 0; i < Models.size() ; i++)
	//{
	//	Models[i].Render(glRegular_program);
	//}
	 //render light cube model
	//LightCube->Render(glRegular_program);
	// Render GeometryModels
	//GeomTriangle->Render();
	 //Render TesselationModels
	//TessModel->Render();

	 //Render Terrain
	//MountainTerrain->RenderTerrain(glm::mat4(), *sceneCamera, *sceneLight, glTerrainProgram);
	// Render Skybox
	Game_SkyBox->RenderSkybox(glSkyBoxProgram);

	//Render 3D Models
	//my3DModel->Draw();
	//myPlayerModel->Draw();

	for (unsigned int i = 0; i < CurtainCloth->m_Cloth_Parts.size(); i++)
	{
		CurtainCloth->m_Cloth_Parts[i]->Render();
	}
 
	if (SphereActive == true)
	{
		Sphere->Render(glRegular_program);
	}

	if (WindActive)
	{
		WindBox->Render(glRegular_program);
	}
	
	Pyramid->Render(glRegular_program);

	Ground->Render(glRegular_program);

	if (Display_UI)
	{
		for (unsigned int i = 0; i < TextLabelVec.size(); i++)
		{
			TextLabelVec[i]->Render();
		}

		SphereActivity->Render();
		Colour_Txt->Render();

		Instructions->Render();
		Restart_Txt->Render();
		Space_Txt->Render();

	}

	glDisable(GL_BLEND);

	glutSwapBuffers();
}

/*
* Function - UpdateCamera()
* Updates camera view matrix as well as movement input by the user

*/
void
GameScene::UpdateCamera()
{
	// update camera look at
	view = glm::lookAt(sceneCamera->m_CameraPosition,
		sceneCamera->m_CameraPosition + sceneCamera->m_CameraFront,
		sceneCamera->m_CamUp);

	sceneCamera->ViewMatrix = view;

	// check for camera movement
	sceneCamera->MoveCamera();
}

/*
* Function - UpdateGameWorld()
* Updates all entities within the game and handles main game loop / processes

*/
void 
GameScene::UpdateGameWorld()
{

	CheckInput();

	Ground->UpdateModel();

	// Update Skybox
	Game_SkyBox->UpdateModel();

	for (unsigned int i = 0; i < Models.size(); i++)
	{
		//Models[i].UpdateModel();
	}

	LightCube->MoveLightSource();
	LightCube->UpdateModel();

	// check if scene is to be restarted 
	RestartGame();

	ClothPhysics->UpdatePhysics();

	for (unsigned int i = 0; i < m_PickedParticles.size(); i++)
	{
		if (m_PickedParticles.size() > 0)
		{
			m_PickedParticles[i]->FollowMouse(sceneCamera->m_CameraPosition, _RayPickDir);
		}
	}

	if (SphereActive == true)
	{
		Sphere->UpdateModel();
		SphereMove();
	}

	if (RandomWind)
	{
		RandomlyMoveWind();
	}

	if (WindActive)
	{
		WindBox->UpdateModel();
	}

	

	Pyramid->UpdateModel();
	
	UpdateClothSize();

	Update_Txt();

	glutPostRedisplay();
}

/*
* Function - RestartGame()
* Checks if the game is to be reset based on user input

*/
void
GameScene::RestartGame()
{
	// reset the camera and light pos
	if (keyState[(unsigned char) 'r'] == BUTTON_DOWN)
	{
		LightCube->m_ModelPosition = Light_StartPos;
		sceneCamera->m_CameraPosition = Camera_StartPos;

		delete CurtainCloth;
		CurtainCloth = NULL;

		delete ClothPhysics;
		ClothPhysics = NULL;


		UserSelectedHeight = 50;
		UserSelectedWidth = 50;
		UserSelectedHooks = 4;
		UserSelectedLinks = 1;

		// Init cloth stuff
		CurtainCloth = new Cloth(glm::vec3(-150.0f, 50.0f, 0.0f), UserSelectedHeight, UserSelectedWidth, 3.0f, 0.5f, 6.0f, UserSelectedHooks);
		ClothPhysics = new Physics(20, 0, 3, CurtainCloth);
		CurtainCloth->CreateCloth(UserSelectedLinks);
	}
}

/*
* Function - SphereMove()
* Used to move the sphere back and forth past the cloth

*/
void
GameScene::SphereMove()
{	
	if (Sphere != NULL)
	{
		if (Sphere->m_ModelPosition.z >= 200)
		{
			SphereMoveForward = false;
		}
		else if (Sphere->m_ModelPosition.z <= -200)
		{
			SphereMoveForward = true;
		}

		if (SphereMoveForward)
		{
			Sphere->m_ModelPosition -=  Sphere->ModelFront * Sphere->ModelSpeed;
		}
		else
		{
			Sphere->m_ModelPosition += Sphere->ModelFront * Sphere->ModelSpeed;
		}
	}

}

/*
* Function - CheckInput()
* Used to process input of the user for menu controls

*/
void 
GameScene::CheckInput()
{
	// simple clock
	GLfloat _CurrentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f; // get current time
	GLfloat Delta = _CurrentTime - m_PreviousTime;
	m_PreviousTime = _CurrentTime;

	 
	if (keyState[(unsigned char) '1'] == BUTTON_DOWN)
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_FILL, GL_LINE
	}
	if (keyState[(unsigned char) '2'] == BUTTON_DOWN)
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_FILL, GL_LINE
	}

	//close window
	if (keyState[(unsigned char)27] == BUTTON_DOWN)
	{
		exit(0);
	}

	Sphere_TimeRemaining -= Delta;
	Structure_TimeRemaining -= Delta;
	ColorRandTime -= Delta;

	if (Sphere_TimeRemaining <= 0.0f)
	{
		if (keyState[(unsigned char) '9'] == BUTTON_DOWN)
		{
			SphereActive = !SphereActive;

			if (SphereActive)
			{
				SphereActivity->setText("9. Sphere: Active");
				SphereActivity->setColor(glm::vec3(0.0f, 1.0f, 1.0f));
			}
			else
			{
				SphereActivity->setText("9. Sphere: Inactive");
				SphereActivity->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
			}
			
			Sphere_TimeRemaining = Time_Countdown;
		}
	}

	if (Sphere_TimeRemaining <= 0.0f)
	{
		if (keyState[(unsigned char) '8'] == BUTTON_DOWN)
		{
			b_RainbowCloth = !b_RainbowCloth;
			Sphere_TimeRemaining = Time_Countdown;

			if (b_RainbowCloth)
			{
				Colour_Txt->setText("8. Color: Cycling");
				Colour_Txt->setColor(glm::vec3(0.0f, 1.0f, 1.0f));
			}
			else
			{
				Colour_Txt->setText("8. Color: Set");
				Colour_Txt->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
			}
		}

	}
	

	
	// UI Controls
	Display_Time_Remaining -= Delta;
	if (Display_Time_Remaining <= 0.0f)
	{
		if (keyState[(unsigned char) ' '] == BUTTON_DOWN)
		{
			Display_Time_Remaining = Time_Countdown;
			Display_UI = !Display_UI;
		}
	}

	if (keyState[(unsigned char) '1'] == BUTTON_DOWN)
	{
		Selected_Attribute = CLOTHSCALE;
		for (unsigned int i = 0; i < TextLabelVec.size(); i++)
		{
			TextLabelVec[i]->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
		}

		Height->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
		Width->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
	}

	if (keyState[(unsigned char) '2'] == BUTTON_DOWN)
	{
		Selected_Attribute = HOOKSIZE;
		for (unsigned int i = 0; i < TextLabelVec.size(); i++)
		{
			TextLabelVec[i]->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
		}

		Hooks->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
	}

	if (keyState[(unsigned char) '3'] == BUTTON_DOWN)
	{
		Selected_Attribute = MOVEHOOKS;
		for (unsigned int i = 0; i < TextLabelVec.size(); i++)
		{
			TextLabelVec[i]->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
		}

		MoveHooks_Txt->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
	}

	if (keyState[(unsigned char) '4'] == BUTTON_DOWN)
	{
		Selected_Attribute = CLOTHSTRUCTURE;
		for (unsigned int i = 0; i < TextLabelVec.size(); i++)
		{
			TextLabelVec[i]->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
		}

		ClothStructure_Txt->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
	}

	
	if (keyState[(unsigned char) '5'] == BUTTON_DOWN)
	{
		Selected_Attribute = MOVEWIND;
		for (unsigned int i = 0; i < TextLabelVec.size(); i++)
		{
			TextLabelVec[i]->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
		}

		MoveWind_Txt->setColor(glm::vec3(0.0f, 1.0f, 0.0f));

		WindActive = true;

	}

	if (keyState[(unsigned char) '6'] == BUTTON_DOWN)
	{
		for (unsigned int i = 0; i < TextLabelVec.size(); i++)
		{
			TextLabelVec[i]->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
		}

		WindSpeed->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
		Selected_Attribute = WINDSPEED;
	}

	
	if (keyState[(unsigned char) '7'] == BUTTON_DOWN)
	{
		for (unsigned int i = 0; i < TextLabelVec.size(); i++)
		{
			TextLabelVec[i]->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
		}

		RandomiseWind->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
		RandomiseWind->setText("7. Randomise Wind : Active");

		RandomWind = true;
		Selected_Attribute = RANDWIND;
	}

	if (Selected_Attribute != MOVEWIND)
	{
		WindActive = false;
	}
	if (Selected_Attribute != RANDWIND)
	{
		RandomWind = false;
		RandomiseWind->setText("7. Randomise Wind : Inactive");
	}

	if (keyState[(unsigned char) '0'] == BUTTON_DOWN)
	{
		DetatchHooks();
	}
	
}

/*
* Function - UpdateClothSize()
* Used to check the characteristics of the cloth and update/ create a new cloth if needed

*/
void
GameScene::UpdateClothSize()
{
	bool ReCreate = false;

	if (CurtainCloth->m_ClothWidth != UserSelectedWidth || 
			CurtainCloth->m_ClothHeight != UserSelectedHeight ||
					CurtainCloth->m_NumberLinks != UserSelectedLinks)
	{
		ReCreate = true;
	}

	if (ReCreate)
	{
		delete CurtainCloth;
		CurtainCloth = NULL;

		delete ClothPhysics;
		ClothPhysics = NULL;

		// Init cloth stuff
		UserSelectedHooks = 4;

		CurtainCloth = new Cloth(glm::vec3(-150.0f, 50.0f, 0.0f), UserSelectedWidth, UserSelectedHeight, 3.0f, 0.5f, 6.0f, UserSelectedHooks);
		ClothPhysics = new Physics(20, 0, 3, CurtainCloth);
		CurtainCloth->CreateCloth(UserSelectedLinks);
	}
}

/*
* Function - Update_Txt()
* Updates the text size values of the cloth

*/
void 
GameScene::Update_Txt()
{
	std::string CurrHeight = "1. Height: ";
	std::string f_str = std::to_string(CurtainCloth->m_ClothHeight);
	CurrHeight += f_str;;
	Height->setText(CurrHeight);

	std::string CurrWidth = "1. Width: ";
	f_str = std::to_string(CurtainCloth->m_ClothWidth);
	CurrWidth += f_str;;
	Width->setText(CurrWidth);
}

/*
* Function - UpdateWidth()
* Updates the width of the cloth

*/
void 
GameScene::UpdateWidth(int _Value)
{
	if (_Value == -1)
	{
		if (CurtainCloth->m_ClothWidth > 5)
		{
			UserSelectedWidth += _Value;
		}
	}
	else if (_Value == 1)
	{
		if (CurtainCloth->m_ClothWidth < 100)
		{
			UserSelectedWidth += _Value;
		}
	}
}

/*
* Function - UpdateHeight()
* Updates the height of the cloth

*/
void
GameScene::UpdateHeight(int _Value)
{
	if (_Value == -1)
	{
		if (CurtainCloth->m_ClothHeight > 5)
		{
			UserSelectedHeight += _Value;
		}
	}
	else if (_Value == 1)
	{
		if (CurtainCloth->m_ClothHeight < 100)
		{
			UserSelectedHeight += _Value;
		}
	}
}

/*
* Function - UpdateHooks()
* Updates the number of hooks that the cloth has

*/
void
GameScene::UpdateHooks(int _Value)
{
	bool Recreate = false;

	if (_Value == -1)
	{
		if (UserSelectedHooks > 1)
		{
			UserSelectedHooks += _Value;
			Recreate = true;
		}
	}
	else if (_Value == 1)
	{
		if (UserSelectedHooks < CurtainCloth->m_ClothWidth / 2)
		{
			UserSelectedHooks += _Value;
			Recreate = true;
		}
	}

	if (Recreate)
	{
		delete CurtainCloth;
		CurtainCloth = NULL;

		delete ClothPhysics;
		ClothPhysics = NULL;

		// Init cloth stuff

		CurtainCloth = new Cloth(glm::vec3(-150.0f, 50.0f, 0.0f), UserSelectedWidth, UserSelectedHeight, 3.0f, 0.5f, 6.0f, UserSelectedHooks);
		ClothPhysics = new Physics(20, 0, 3, CurtainCloth);
		CurtainCloth->CreateCloth(UserSelectedLinks);
	}



}

/*
* Function - MoveHooks()
* Moves the pinned particles along the top of the cloth

*/
void
GameScene::MoveHooks(bool _moveRight)
{
	if (_moveRight)
	{
		for (unsigned int i = 0; i < CurtainCloth->m_Pinned_Particles.size(); i++)
		{
			if (i > 0 && i != CurtainCloth->m_Pinned_Particles.size() - 1)
			{
				GLfloat DistanceFromPrevious = abs(glm::distance(CurtainCloth->m_Pinned_Particles[i - 1]->m_CurrentPosition, CurtainCloth->m_Pinned_Particles[i]->m_CurrentPosition));

				
				if (DistanceFromPrevious < CurtainCloth->m_ClothWidth / CurtainCloth->m_NumHooks)
				{
					GLfloat FinalDist = abs(glm::distance(CurtainCloth->m_Pinned_Particles.back()->m_CurrentPosition, CurtainCloth->m_Pinned_Particles[CurtainCloth->m_Pinned_Particles.size() - 2]->m_CurrentPosition));
					if (FinalDist > CurtainCloth->m_ClothWidth / CurtainCloth->m_NumHooks)
					{
						CurtainCloth->m_Pinned_Particles[i]->m_Pinned_Position.x += 1.0f;
					}
				}
			}
			else if (i != CurtainCloth->m_Pinned_Particles.size() - 1)
			{
				GLfloat FinalDist = abs(glm::distance(CurtainCloth->m_Pinned_Particles.back()->m_CurrentPosition, CurtainCloth->m_Pinned_Particles[CurtainCloth->m_Pinned_Particles.size() - 2]->m_CurrentPosition));
				if (FinalDist > CurtainCloth->m_ClothWidth / CurtainCloth->m_NumHooks)
				{
					CurtainCloth->m_Pinned_Particles[i]->m_Pinned_Position.x += 1.0f;
				}		
			}
			
		}
	}

	else
	{
		for (unsigned int i = 0; i < CurtainCloth->m_Pinned_Particles.size(); i++)
		{
			if (i == 0)
			{
				GLfloat DistanceFromStartToEnd = abs(glm::distance(CurtainCloth->m_Pinned_Particles[0]->m_CurrentPosition, CurtainCloth->m_Pinned_Particles[CurtainCloth->m_Pinned_Particles.size() - 1]->m_CurrentPosition));

				if (DistanceFromStartToEnd < (CurtainCloth->m_ClothWidth) * CurtainCloth->m_Cloth_Resting_Distance)
				{
					CurtainCloth->m_Pinned_Particles[i]->m_Pinned_Position.x -= 1.0f;
				}
				

			}
			else if (i != CurtainCloth->m_Pinned_Particles.size() - 1)
			{
				GLfloat DistanceFromPrevious = abs(glm::distance(CurtainCloth->m_Pinned_Particles[i]->m_CurrentPosition, CurtainCloth->m_Pinned_Particles[i - 1]->m_CurrentPosition));
				if (DistanceFromPrevious > (CurtainCloth->m_ClothWidth *  CurtainCloth->m_Cloth_Resting_Distance) / CurtainCloth->m_NumHooks)
				{
					CurtainCloth->m_Pinned_Particles[i]->m_Pinned_Position.x -= 1.0f;
				}
			}
		}
	}
}

/*
* Function - UpdateClothStructure()
* Changes the number of the links that the cloth has between 2 - 4 and creates a new cloth when updated

*/
void
GameScene::UpdateClothStructure()
{
	if (Structure_TimeRemaining <= 0.0f)
	{
		// change structure type
		UserSelectedLinks++;

		if (UserSelectedLinks > 3)
		{
			UserSelectedLinks = 1;
		}

		Structure_TimeRemaining = Time_Countdown;
	}

	switch (UserSelectedLinks)
	{
	case 1:
		ClothStructure_Txt->setText("4. Cloth Structure: Weak Links");
			break;

	case 2:
		ClothStructure_Txt->setText("4. Cloth Structure: Medium Links");
		break;

	case 3:
		ClothStructure_Txt->setText("4. Cloth Structure: Strong Links");
		break;

	default:
		break;
	}
}

/*
* Function - MoveWind()
*Used to move the position of the wind box when active

*/
void
GameScene::MoveWind(int _Value, bool X_Axis)
{
	glm::vec3 WindBoxSpeed = glm::vec3(3.0f, 3.0f, 3.0f);

	// Left
	if (_Value == -1 && X_Axis == true)
	{
		WindBox->m_ModelPosition -= glm::normalize(glm::cross(WindBox->ModelFront, WindBox->ModelUp)) * WindBoxSpeed;
	}
	//Right
	if (_Value == 1 && X_Axis == true)
	{
		WindBox->m_ModelPosition += glm::normalize(glm::cross(WindBox->ModelFront, WindBox->ModelUp)) * WindBoxSpeed;
	}
	//move up
	if (_Value == 1 && X_Axis == false)
	{
		WindBox->m_ModelPosition += WindBox->ModelUp * WindBoxSpeed;
	}
	//move down
	if (_Value == -1 && X_Axis == false)
	{
		WindBox->m_ModelPosition -= WindBox->ModelUp * WindBoxSpeed;
	}
}

/*
* Function - RandomlyMoveWind()
* Causes the wind box to move around the cloth randomly to create a random wind effect

*/
void
GameScene::RandomlyMoveWind()
{
	GLfloat MoveDist = CurtainCloth->m_ClothWidth * CurtainCloth->m_Cloth_Resting_Distance;

		if (RamdWindPos.x >=  -100 + MoveDist)
		{
			MoveRandWindLeft = true;
		}
		else if (RamdWindPos.x <= -MoveDist)
		{
			MoveRandWindLeft = false;
		}

		if (MoveRandWindLeft)
		{
			RamdWindPos.x -= 1.0f;
		}
		else
		{
			RamdWindPos.x += 1.0f;
		}

		int Rand = (rand() % 100);

		if (Rand <= 5)
		{
			// change the winds y position
			int Height = CurtainCloth->m_ClothHeight * CurtainCloth->m_Cloth_Resting_Distance;
			
			int RandHeight = (rand() %  Height);

			RamdWindPos.y = RandHeight;
		}

		Pyramid->m_ModelPosition = RamdWindPos;
}

/*
* Function - UpdateWindSpeed()
* Causes the wind box to move around the cloth randomly to create a random wind effect

*/
void
GameScene::UpdateWindSpeed(int _Value)
{
	if (_Value == -1)
	{
		if (UserSelectedWindSpeed > 100)
		{
			UserSelectedWindSpeed -= 50;
		}
	}
	else if (_Value == 1)
	{
		if (UserSelectedWindSpeed < 4000)
		{
			UserSelectedWindSpeed += 50;
		}
	}

	std::string Speed = "6. Wind Speed: ";
	std::string f_str = std::to_string(UserSelectedWindSpeed);
	Speed += f_str;;
	WindSpeed->setText(Speed);
}

/*
* Function - DetatchHooks()
* Removes all pinned particles from the cloth causing it to fall due to gravity

*/
void 
GameScene::DetatchHooks()
{
	if (CurtainCloth->m_Pinned_Particles.size() > 0)
	{
		for (unsigned int i = 0; i < CurtainCloth->m_Cloth_Parts.size(); i++)
		{
			if (CurtainCloth->m_Cloth_Parts[i]->m_Pinned)
			{
				CurtainCloth->m_Cloth_Parts.erase(CurtainCloth->m_Cloth_Parts.begin() + i);
				i--;
			}
			
		}

		CurtainCloth->m_Pinned_Particles.clear();
	}
}