#pragma once

#include <iostream>

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "ShaderLoader.h"
#include "Dependencies\soil\SOIL.h"

// Math libraries
#include "Dependencies\glm\glm\glm.hpp"
#include "Dependencies\glm\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\glm\gtc\type_ptr.hpp"

#include "Camera.h"
#include "Model.h"
#include "ShaderLoader.h"
#include "Utils.h"
#include "LightSource.h"
#include <string>
#include <vector>
#include "Cloth.h"
#include "Physics.h"
#include "TextLabel.h"

//class TextLabel;
class Particle;
class Cloth;
class Physics;
class SkyBox;
class Model;
class Camera;
class Terrain;
class TextLabel;

struct Position;
enum ModelType;

enum SelectedOption
{
	CLOTHSCALE = 1,
	HOOKSIZE,
	CLOTHSTRUCTURE,
	MOVEHOOKS,
	MOVEWIND,
	WINDSPEED,
	RANDWIND,
};

class GameScene
{
private:


	// singleton
	GameScene();
	GameScene(const GameScene& _kr);

public:

	// programs
	GLuint glprogram;
	GLuint glRegular_program;
	GLuint glTerrainProgram;
	GLuint glSkyBoxProgram;
	GLuint glModelProgram;
	GLuint glGeometryProgram;
	GLuint glTesselationProgram;
	GLuint glColorProgram;

	~GameScene();

	// Keyboard Input
	unsigned char keyState[255];

	// Initialistion
	void InitGameWorld();
	void Init_Shapes();
	void Init_Camera();
	void Init_Skybox();
	void Init_Programmes();

		// Updating
	void UpdateGameWorld();

	// Rendering
	void RenderGameWorld();

	// Camera
	void UpdateCamera();
	Camera* sceneCamera;
	glm::mat4 view;
	glm::mat4 projection;

	// Lighting
	Light* sceneLight;


	// Shapes
	std::vector<Model> Models;

	//Skybox
	SkyBox* Game_SkyBox;

	// Singleton Methods
	static GameScene& GetInstance();

	// Restart
	glm::vec3 Light_StartPos;
	glm::vec3 Camera_StartPos;

	void RestartGame();


	Physics* ClothPhysics;
	Cloth* CurtainCloth;


	// mouse picking
	glm::vec3 _RayPickDir;
	std::vector<Particle*> m_PickedParticles;
	bool Particle_Dragging;


	// collisions
	glm::vec3 ShapeStartPos;
	Model* Sphere;
	Model* Pyramid;
	Model* Capsule;
	Model* WindBox;
	bool WindActive = false;
	bool SphereActive = false;
	bool SphereMoveForward = true;
	bool RandomWind = false;

	void SphereMove();

	// Input
	void CheckInput();
	void UpdateWidth(int _Value);
	void UpdateHeight(int _Value);
	void UpdateHooks(int _Value);
	void UpdateClothStructure();
	void MoveHooks(bool _moveRight);
	void MoveWind(int _Value, bool X_Axis);
	void UpdateWindSpeed(int _Value);
	void DetatchHooks();

	int UserSelectedWidth;
	int UserSelectedHeight;
	int UserSelectedHooks;
	int UserSelectedLinks;
	bool CurrentlySelecting = false;
	int UserSelectedWindSpeed = 500.0f;

	void UpdateClothSize();
	void RandomlyMoveWind();
	


	// UI
	TextLabel* Width;
	TextLabel* Height;
	TextLabel* Hooks;
	TextLabel* SphereActivity;
	TextLabel* MoveHooks_Txt;
	TextLabel* ClothStructure_Txt;
	TextLabel* MoveWind_Txt;
	TextLabel* RandomiseWind;
	TextLabel* Colour_Txt;
	TextLabel* Detatch_Txt;
	TextLabel* WindSpeed;
	TextLabel* Restart_Txt;
	TextLabel* Space_Txt;
	TextLabel* Instructions;

	Model* Ground;

	std::vector<TextLabel*> TextLabelVec;

	SelectedOption Selected_Attribute;

	void Update_Txt();

	bool Display_UI = true;
	const GLfloat Time_Countdown = 0.2f;
	GLfloat Display_Time_Remaining = Time_Countdown;
	GLfloat m_PreviousTime;
	bool b_RainbowCloth = false;

	const GLfloat ConstColorTime = 0.002f;
	GLfloat ColorRandTime = ConstColorTime;
	

	GLfloat Sphere_TimeRemaining = Time_Countdown;
	GLfloat Structure_TimeRemaining = Time_Countdown;

	glm::vec3 RamdWindPos = glm::vec3(0.0f, 100.0f, 0.0f);
	bool MoveRandWindLeft = true;

protected:
	static GameScene* s_pGameScene;

};

