// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
#include "Shadow.h"
#include "Camera.h"
#include "QuadFloor.h"
#include "Light.h"
#include "Model.h"
#include "Cube.h"
#include "Sphere.h"
#include "QuadWall.h"
#include "Material.h"
#include "Vector3.h"
#include "Reflection.h"

class Scene{

public:
	Scene(Input *in);
	// Main render function
	void render(float dt);
	// Handle input function that receives delta time from parent.
	void handleInput(float dt);
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);

protected:
	// configure opengl render pipeline
	void initialiseOpenGL();
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void calculateFPS();

	// draw primitive functions
	QuadFloor quadFloor;
	Cube cube, cube2, moveableCube;
	Vector3 moveableCubePos = {20,3,20};
	Sphere sphere, sphere2;
	QuadWall wall;

	// Helper Functions
	void AddShadow();
	void AddReflections();
	void AddSkyBox();
	void AddLighting(float dt);
	void AddModels(float dt);
	void AddFloor();
	void AddShapes(float dt);

	void textCameraPositioning();
	void textCameraNumber();
	void CameraControls(float dt);
	void LightControls(float dt);
	void GeneralControls();
	void PlaceCube(GLfloat, GLfloat, GLfloat);
	void LampShadowHelper(float* shadowMatrix, float lightPos[4], GLfloat floor[12], float lampPos[3]);
	void MoveableCubeControls(float dt);
	void Floor();

	//Camera
	Camera* camera0 = new Camera();
	Camera* camera1 = new Camera();
	Camera* camera2 = new Camera();//helicopter
	Camera* camera3 = new Camera();//car
	Camera* camera4 = new Camera();//non glut curser
	Camera* CurrentCameraPointer = nullptr;
	char camNumberText[40] = "cam 1";

	float speed = 5;
	float extraSpeed = 5;
	char posX[40];char posY[40];char posZ[40]; //X,Y,Z POSITION OF CAMERA
	char forwardX[40];char forwardY[40];char forwardZ[40]; //X Y Z FORWARD (LOOK AT)
	char upX[40];char upY[40];char upZ[40]; //X Y Z UP VECTOR
	char pitch[40];char yaw[40];char roll[40]; //Pitch,Yaw,Roll
	int fovAdd = 70;

	//light
	Light light0 = Light(GL_LIGHT0);
	Light light1 = Light(GL_LIGHT1);
	Light light2 = Light(GL_LIGHT2);
	Light light3 = Light(GL_LIGHT3);
	Light light4 = Light(GL_LIGHT4);
	Light light5 = Light(GL_LIGHT5);
	Light light6 = Light(GL_LIGHT6);
	Light light7 = Light(GL_LIGHT7);
	bool isFlashLightOn = false;
	Material material;
	GLfloat houseEmissionSave[4] = { 0,0,0,0 };
	bool isColourLighting = false;

	//Model
	Model policeCar, person, lamp, building2, helicopter, rose, eye;
	string carDirection = "forward";
	float carDistance = 0;
	string chopperDirection = "forward";
	string chopperDirection2 = "left";
	Vector3 choppeDistance = { 0,0,0 };
	float chopperTimer = 0;
	string chopperHoverDirection = "up";
	float chopperHoverTimer = 0;
	Vector3 choppeHoverDistance = { 25,15,50 };
	float chopperRotate = 0;

	//reflection
	Vector3 carPos;
	Reflection magicBox;

	//shadow
	Shadow shadow1;

	//skybox
	GLuint skyBox1, skyBox2, skyBox3, skyBox4, grass_texture, woodPlank, blueRed, moon, red, blue;
	int skyboxNum = 0;
	int skyBoxMax = 3;
	GLfloat moonRotation = 0;

	//general
	bool isPolygonMode = true;
	bool isDotMode = false;
	bool isLineMode = false;
	bool isLightingOn = true;

	// For access to user input.
	Input* input;
		
	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];

};

#endif