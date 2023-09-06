#include "Scene.h"

void RenderCube(); //helper func to create cube with texture and normals
void AddTexture(GLuint texture); //helper func to add texture
void RemoveTexture(); //helper func to remove texture
float houseColourCurrentTimer = 0, lamp2timer = 0, carTimer = 0; //timers for animation

// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	// Other OpenGL / render setting should be applied here.
	CurrentCameraPointer = camera1;
	
	//GENERAL ------------------------------------------------------------------------
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glutSetCursor(GLUT_CURSOR_NONE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);

	//MODEL STUFF ---------------------------------------------------------------------
	if (!policeCar.load("models/Police_Car/PoliceCar.obj", "models/Police_Car/wiggu_vHoodNorm.bmp.png")) {
		printf("Oh no. I can't load this file.");
	}
	if (!person.load("models/Hugh/Hugh.obj", "models/Hugh/Material53.png")) {
		printf("Oh no. I can't load this file.");
	}
	if (!lamp.load("models/Lamp/fobj_lamp.obj", "models/Lamp/fobj_lamp_s.png")) {
		printf("Oh no. I can't load this file.");
	}
	if (!building2.load("models/Building2/Building_B.obj", "models/Building2/B_Diffuse.png")) {
		printf("Oh no. I can't load this file.");
	}
	if (!helicopter.load("models/helicopter/chopper.obj", "models/helicopter/ec135.bmp")) {
		printf("Oh no. I can't load this file.");
	}

	//TEXTURE STUFF -------------------------------------------------------------------
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	skyBox1 = SOIL_load_OGL_texture("gfx/SkyBoxes/nightSky.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	skyBox2 = SOIL_load_OGL_texture("gfx/SkyBoxes/daySky.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	skyBox3 = SOIL_load_OGL_texture("gfx/skybox.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	skyBox4 = SOIL_load_OGL_texture("gfx/cubeTexture.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	grass_texture = SOIL_load_OGL_texture("gfx/grass.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	blueRed = SOIL_load_OGL_texture("gfx/bluered.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	woodPlank = SOIL_load_OGL_texture("gfx/woodPlank.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	moon = SOIL_load_OGL_texture("gfx/moon.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	red = SOIL_load_OGL_texture("gfx/red.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	blue = SOIL_load_OGL_texture("gfx/blue.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	
	//lights -------------------------------------------------------------------------------
	light0.Enable(); //lmap 1
	//light1.Enable(); //flash light (starts disabled)
	light2.Enable(); //lamp 2
	light3.Enable(); //lamp 3
	light4.Enable(); //lamp 4
	light5.Enable(); //car
	light6.Enable(); //helicopter
	light7.Enable(); //moon
}

void Scene::handleInput(float dt)
{
	CameraControls(dt);
	LightControls(dt);
	GeneralControls();
	MoveableCubeControls(dt);
}

void Scene::update(float dt)
{
	calculateFPS();
}

void Scene::render(float dt) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt(CurrentCameraPointer->GetCameraPosition().x, CurrentCameraPointer->GetCameraPosition().y, CurrentCameraPointer->GetCameraPosition().z, CurrentCameraPointer->GetLookAt().x, CurrentCameraPointer->GetLookAt().y,
		CurrentCameraPointer->GetLookAt().z, CurrentCameraPointer->GetUpVector().x, CurrentCameraPointer->GetUpVector().y, CurrentCameraPointer->GetUpVector().z);
	
	// Render geometry/scene here -------------------------------------

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	AddSkyBox();
	if (isPolygonMode) {
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	else if (isDotMode) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}
	else if (isLineMode) {
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}

	AddFloor();
	AddLighting(dt);
	AddModels(dt);
	AddShapes(dt);
	AddShadow();
	AddReflections(); 
	Floor();
	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0, 0, 0, 0);			// black
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blending function
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = fovAdd; //45 default
	nearPlane = 0.1f;
	farPlane = 300.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	textCameraPositioning();
	textCameraNumber();
}

void Scene::textCameraNumber() {
	//update which camera being used
	if (CurrentCameraPointer == camera0) { //camera1 is a *Camera, CurrentCamera is Camera
		camNumberText[0] = 'C';
		camNumberText[1] = 'A';
		camNumberText[2] = 'M';
		camNumberText[3] = ' ';
		camNumberText[4] = '0';
		camNumberText[5] = ' ';
		camNumberText[6] = ' ';
		camNumberText[7] = ' ';
	}
	else if (CurrentCameraPointer == camera1) { 
		camNumberText[0] = 'C';
		camNumberText[1] = 'A';
		camNumberText[2] = 'M';
		camNumberText[3] = ' ';
		camNumberText[4] = '1';
		camNumberText[5] = '(';
		camNumberText[6] = 'F';
		camNumberText[7] = ')';
	}
	else if (CurrentCameraPointer == camera0) { 
		camNumberText[0] = 'C';
		camNumberText[1] = 'A';
		camNumberText[2] = 'M';
		camNumberText[3] = ' ';
		camNumberText[4] = '2';
		camNumberText[5] = ' ';
		camNumberText[6] = ' ';
		camNumberText[7] = ' ';
	}
	else if (CurrentCameraPointer == camera0) {
		camNumberText[0] = 'C';
		camNumberText[1] = 'A';
		camNumberText[2] = 'M';
		camNumberText[3] = ' ';
		camNumberText[4] = '3';
		camNumberText[5] = ' ';
		camNumberText[6] = ' ';
		camNumberText[7] = ' ';
	}
	else if (CurrentCameraPointer == camera4) {
		camNumberText[0] = 'C';
		camNumberText[1] = 'A';
		camNumberText[2] = 'M';
		camNumberText[3] = ' ';
		camNumberText[4] = '4';
		camNumberText[5] = ' ';
		camNumberText[6] = ' ';
		camNumberText[7] = ' ';
	}

	glDisable(GL_LIGHTING);
	
	displayText(0.9f, 0.9f, 1.f, 0.78f, 0.90f, camNumberText); // Render current mouse position and frames per second.
}

void Scene::textCameraPositioning() {
	glDisable(GL_LIGHTING);
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);

	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);

	////////////////////// POSITION OF CAMERA
	sprintf_s(posX, "Pos X: %f", CurrentCameraPointer->GetCameraPosition().x);
	sprintf_s(posY, "Pos Y: %f", CurrentCameraPointer->GetCameraPosition().y);
	sprintf_s(posZ, "Pos Z: %f", CurrentCameraPointer->GetCameraPosition().z);

	displayText(-1.f, 0.87f, 0.0f, 1.0f, 0.1f, posX);
	displayText(-1.f, 0.81f, 0.0f, 1.0f, 0.1f, posY);
	displayText(-1.f, 0.75f, 0.0f, 1.0f, 0.1f, posZ);

	////////////////// LOOK AT (FORWARD)

	sprintf_s(forwardX, "forward X: %f", CurrentCameraPointer->GetLookAt().x);
	sprintf_s(forwardY, "forward Y: %f", CurrentCameraPointer->GetLookAt().y);
	sprintf_s(forwardZ, "forward Z: %f", CurrentCameraPointer->GetLookAt().z);

	displayText(-1.f, 0.69f, 1.0f, 0.0f, 0.1f, forwardX);
	displayText(-1.f, 0.63f, 1.0f, 0.0f, 0.1f, forwardY);
	displayText(-1.f, 0.57f, 1.0f, 0.0f, 0.1f, forwardZ);

	///////////////////// UP VECTOR

	sprintf_s(upX, "Up X: %f", CurrentCameraPointer->GetUpVector().x);
	sprintf_s(upY, "Up Y: %f", CurrentCameraPointer->GetUpVector().y);
	sprintf_s(upZ, "Up Z: %f", CurrentCameraPointer->GetUpVector().z);

	displayText(-1.f, 0.51f, 0.0f, 1.0f, 0.1f, upX);
	displayText(-1.f, 0.45f, 0.0f, 1.0f, 0.1f, upY);
	displayText(-1.f, 0.39f, 0.0f, 1.0f, 0.1f, upZ);

	////////////////////////// pitch, yaw, roll
	sprintf_s(pitch, "Pitch : %f", CurrentCameraPointer->GetPitch());
	sprintf_s(yaw, "Yaw : %f", CurrentCameraPointer->GetYaw());
	sprintf_s(roll, "Roll : %f", CurrentCameraPointer->GetRoll());

	displayText(-1.f, 0.33f, 1.0f, 0.0f, 0.1f, pitch);
	displayText(-1.f, 0.27f, 1.0f, 0.0f, 0.1f, yaw);
	displayText(-1.f, 0.21f, 1.0f, 0.0f, 0.1f, roll);
	glEnable(GL_LIGHTING);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}

void Scene::CameraControls(float dt) {

	if (input->isKeyDown('0')) {
		CurrentCameraPointer = camera0;
	}
	else if (input->isKeyDown('1')) {
		CurrentCameraPointer = camera1;
	}
	else if (input->isKeyDown('2')) {
		CurrentCameraPointer = camera2;
	}
	else if (input->isKeyDown('3')) {
		CurrentCameraPointer = camera3;
	}
	else if (input->isKeyDown('4')) {
		CurrentCameraPointer = camera4;
	}

	if (CurrentCameraPointer == camera0 || CurrentCameraPointer == camera1) {
			//Position of camera
			if (input->isKeyDown('w')) 
				CurrentCameraPointer->moveForward(dt);
			if (input->isKeyDown('a'))
				CurrentCameraPointer->moveLeft(dt);
			if (input->isKeyDown('s'))
				CurrentCameraPointer->moveBackwards(dt);
			if (input->isKeyDown('d'))
				CurrentCameraPointer->moveRight(dt);

			if (input->isKeyDown('q'))
				CurrentCameraPointer->SetCameraPositionY(speed * dt);
			if (input->isKeyDown('e'))
				CurrentCameraPointer->SetCameraPositionY(-speed * dt);

			// mouse pitch,yaw,roll
			float mouseX = input->getMouseX();
			float mouseY = input->getMouseY();
			float centreX = width / 2;
			float centreY = height / 2;

			glutWarpPointer(centreX, centreY);

			float windowXdistance = mouseX - centreX;
			float windowYdistance = mouseY - centreY;

			if (windowXdistance != 0)
				CurrentCameraPointer->SetYaw(windowXdistance * extraSpeed * dt);
			if (windowYdistance != 0)
				CurrentCameraPointer->SetPitch(-windowYdistance * extraSpeed * dt);

			CurrentCameraPointer->UpdateCamera();
	}
	else if (CurrentCameraPointer == camera2) { //helicopter
			//Position of camera
		camera2->SetHelicopterPitch(360);

		float mouseX = input->getMouseX();
		float mouseY = input->getMouseY();
		float centreX = width / 2;
		float centreY = height / 2;

		glutWarpPointer(centreX, centreY);

		float windowXdistance = mouseX - centreX;

		if (windowXdistance != 0)
			CurrentCameraPointer->SetYaw(windowXdistance * extraSpeed * dt);

		camera2->SetCameraPosition(choppeHoverDistance.x, choppeHoverDistance.y + 1, choppeHoverDistance.z);
		CurrentCameraPointer->UpdateCamera();
	}
	else if (CurrentCameraPointer == camera3) { //car
		//Position of camera
		camera3->SetHelicopterPitch(360);

		float mouseX = input->getMouseX();
		float mouseY = input->getMouseY();
		float centreX = width / 2;
		float centreY = height / 2;

		glutWarpPointer(centreX, centreY);

		float windowXdistance = mouseX - centreX;

		if (windowXdistance != 0)
			CurrentCameraPointer->SetYaw(windowXdistance * extraSpeed * dt);

		camera3->SetCameraPosition(50, 0.5, carDistance);

		CurrentCameraPointer->UpdateCamera();
	}
	else if (CurrentCameraPointer == camera4) {
		//Position of camera
		if (input->isKeyDown('w'))
			camera4->SetCameraPositionY(speed * dt);
		if (input->isKeyDown('a'))
			camera4->SetCameraPositionX(-speed * dt);
		if (input->isKeyDown('s'))
			camera4->SetCameraPositionY(-speed * dt);
		if (input->isKeyDown('d'))
			camera4->SetCameraPositionX(speed * dt);

		if (input->isKeyDown('q'))
			camera4->SetCameraPositionZ(speed * dt);
		if (input->isKeyDown('e'))
			camera4->SetCameraPositionZ(-speed * dt);

		//pitch,yaw,roll

		if (input->isKeyDown('z'))
			camera4->SetPitch(speed * extraSpeed * dt); camera4->UpdateCamera();

		if (input->isKeyDown('x'))
			camera4->SetYaw(speed * extraSpeed * dt); camera4->UpdateCamera();

		if (input->isKeyDown('c'))
			camera4->SetRoll(speed * extraSpeed * dt); camera4->UpdateCamera();

	}
	
}

void RenderCube() {

	glBegin(GL_QUADS);
	//front face
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0, 0, 0);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.5f, 0.25f);
	glVertex3f(0, 1, 0);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(1, 1, 0);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.25f, 0.5f);
	glVertex3f(1, 0, 0);

	//left
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.25, 0.5);
	glVertex3f(1, 0, 0);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.25, 0.25);
	glVertex3f(1, 1, 0);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0, 0.25);
	glVertex3f(1, 1, 1);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0, 0.5);
	glVertex3f(1, 0, 1);

	//right
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.75, 0.5);
	glVertex3f(0, 0, 1);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.75, 0.25);
	glVertex3f(0, 1, 1);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.5, 0.25);
	glVertex3f(0, 1, 0);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.5, 0.5);
	glVertex3f(0, 0, 0);

	//Back
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.75, 0.5);
	glVertex3f(0, 0, 1);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1, 0.5);
	glVertex3f(1, 0, 1);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1, 0.25);
	glVertex3f(1, 1, 1);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.75, 0.25);
	glVertex3f(0, 1, 1);

	//top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.25, 0);
	glVertex3f(1, 1, 1);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.25, 0.25);
	glVertex3f(1, 1, 0);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.5, 0.25);
	glVertex3f(0, 1, 0);

	glNormal3f(0.0f, 11.0f, 0.0f);
	glTexCoord2f(0.5, 0);
	glVertex3f(0, 1, 1);

	//bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.25, 0.75);
	glVertex3f(0, 0, 0);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.5, 0.75);
	glVertex3f(1, 0, 0);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.5, 0.5);
	glVertex3f(1, 0, 1);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.25, 0.5);
	glVertex3f(0, 0, 1);

	glEnd();

}

void Scene::AddLighting(float dt) {

	if (isLightingOn) {
		light0.Enable();
		light2.Enable();
		light3.Enable();
		light4.Enable();
		light5.Enable();
		light6.Enable();
		light7.Enable();

		//flash light //////////////////////////////////////////////
		light1.SetIntensity(5);
		light1.SetDiffuse(4, 4, 4, 0.5);
		light1.SetSpecular(0.7, 0.7, 0.7, 1);
		light1.SetAmbient(0, 0, 0, 1);
		light1.SetSpotDirection(camera1->GetForward().x, camera1->GetForward().y, camera1->GetForward().z);
		light1.SetPosition(camera1->GetCameraPosition().x, camera1->GetCameraPosition().y, camera1->GetCameraPosition().z, 1);
		light1.SetAttenuation(1, 0.1, 0.05);
		glPushMatrix();
		glTranslatef(light1.GetPositionX(), light1.GetPositionY() - 0.5, light1.GetPositionZ());
		glScalef(0.1, 0.1, 0.1);
		glPopMatrix();
		light1.Update();

#pragma region lamps
		//LAMP 1 /////////////////////////////////////////////////////
		light0.SetAmbient(0, 0, 0, 1);
		light0.SetSpotDirection(0, -1, 0);
		light0.SetPosition(40, 15, 33, 1);
		light0.SetDiffuse(0.7, 0.7, 0, 1);
		light0.SetAttenuation(1, 0, 0);
		light0.SetIntensity(30);
		light0.Update();

		//LAMP 2 ///////////////////////////////////////////////////////
		if (lamp2timer > 0.5) {
			lamp2timer = 0;
			if (light2.isOn == true) {
				light2.isOn = false;
				light2.Disable();
			}
			else {
				light2.isOn = true;
				light2.Enable();
			}

		}
		else {
			lamp2timer += dt;
		}
		light2.SetSpotDirection(0, -1, 0);
		light2.SetAmbient(0, 0, 0, 1);
		light2.SetPosition(60, 15, 33, 1);
		glPushMatrix();
		glTranslatef(60, 15, 33);
		glPopMatrix();
		light2.Update();

		//LAMP 3 /////////////////////////////////////////////////////
		light3.SetAmbient(0, 0, 0, 1);
		light3.SetDiffuse(0.9, 0.0, 0, 1);
		light3.SetSpotDirection(0, -1, 0);
		light3.SetPosition(40, 15, 66, 1);
		light3.SetAttenuation(1, 0, 0);
		light3.SetIntensity(40);
		light3.Update();

		//LAMP 4 /////////////////////////////////////////////////////
		light4.SetAmbient(0, 0, 0, 1);
		light4.SetDiffuse(0.2, 0.31, 0.9, 1);
		light4.SetSpotDirection(0, -1, 0);
		light4.SetPosition(60, 30, 66, 1);
		light4.SetAttenuation(1, 0, 0);
		light4.SetIntensity(40);
		light4.Update();
#pragma endregion

		//CAR
		glPushMatrix();
		if (carDirection == "forward") {
			light5.SetSpotDirection(0, -0.5, 1);
		}
		else {
			light5.SetSpotDirection(0, -0.5, -1);
		}

		light5.SetAmbient(0, 0, 0, 1);
		light5.SetPosition(50, 5, carDistance, 1);
		light5.SetDiffuse(1, 1, 0, 0.7);
		light5.SetAttenuation(1, 0, 0);
		light5.SetIntensity(10);
		light5.Update();
		glPopMatrix();

		//chopper
		glPushMatrix();
		if (chopperTimer > 0.1) { //add to chopper timer
			chopperTimer = 0;
			if (chopperDirection == "forward") { //if forward
				choppeDistance.z += 0.05;
				if (choppeDistance.z > 1) {
					chopperDirection = "backward";
				}
			}
			else {
				choppeDistance.z -= 0.05;
				if (choppeDistance.z < -1) {
					chopperDirection = "forward";
				}
			}

			if (chopperDirection2 == "left") { //if forward
				choppeDistance.x += 0.1;
				if (choppeDistance.x > 1) {
					chopperDirection2 = "right";
				}
			}
			else {
				choppeDistance.x -= 0.1;
				if (choppeDistance.x < -1) {
					chopperDirection2 = "left";
				}
			}
		}
		else {
			chopperTimer += dt;
		}

		light6.SetSpotDirection(choppeDistance.x, -1, choppeDistance.z);
		light6.SetAmbient(0, 0, 0, 1);
		light6.SetPosition(25, 15, 50, 1);
		light6.SetDiffuse(0, 0, 50, 1);
		light6.SetAttenuation(1, 0, 0);
		light6.SetIntensity(50);
		light6.Update();
		glPopMatrix();

		//moon light
		glColor3f(1, 1, 1);
		light7.SetAmbient(0.2, 0.2, 0.2, 0.7);
		light7.SetSpotDirection(0, -1, 0);
		light7.SetPosition(50, 60, 50, 0);
		light7.SetDiffuse(0, 1, 0, 1);
		light7.SetIntensity(5);
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(50, 60, 50);
		RenderCube();
		glEnable(GL_LIGHTING);
		glPopMatrix();
		light7.Update();
	}
	else {
		light0.Disable();
		light1.Disable();
		light2.Disable();
		light3.Disable();
		light4.Disable();
		light5.Disable();
		light6.Disable();
		light7.Disable();
	}
}	

void Scene::LightControls(float dt) {

	if (input->isKeyDown('p')) {
		isColourLighting = !isColourLighting;
		input->setKeyUp('p');
	}
}

void AddTexture(GLuint texture) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f(1.0f, 1.0f, 1.0f);//Make sure the colour is white
}

void RemoveTexture() {
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void Scene::GeneralControls() { 

	//different drawing modes ------------------------------------------------------
	if (input->isKeyDown('Q') && GLUT_ACTIVE_SHIFT == 1) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		isPolygonMode = false;
		isDotMode = false;
		isLineMode = true;
	}
	else if (input->isKeyDown('W') && GLUT_ACTIVE_SHIFT == 1) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		isPolygonMode = true;
		isDotMode = false;
		isLineMode = false;
	}
	else if (input->isKeyDown('E') && GLUT_ACTIVE_SHIFT == 1) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		isPolygonMode = false;
		isDotMode = true;
		isLineMode = false;
	}
	else if (input->isKeyDown('L') && GLUT_ACTIVE_SHIFT == 1) {
		if (isLightingOn == true) {
			isLightingOn = false;
			glDisable(GL_LIGHT0);
			glDisable(GL_LIGHT1);
			input->setKeyUp('L');
		}
		else {
			isLightingOn = true;
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			input->setKeyUp('L');
		}
	}

	//flash light ------------------------------------------------------
	if (input->isKeyDown('f')) {
		if (isFlashLightOn == true) {
			isFlashLightOn = false;
			glDisable(GL_LIGHT1);
			input->setKeyUp('f');
		}
		else {
			isFlashLightOn = true;
			glEnable(GL_LIGHT1);
			input->setKeyUp('f');
		}
	}

	//skybox change ------------------------------------------------------
	if (input->isKeyDown('g')) {

		skyboxNum++;
		input->setKeyUp('g');

		if (skyboxNum > skyBoxMax) {
			skyboxNum = 0;
		}
	}

	
}

void Scene::Floor() {
	//MAKE SURFACE REFLECT ----------------------------------------------
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDisable(GL_DEPTH_TEST);
#pragma region surface
	glBegin(GL_QUADS);
	glVertex3f(-1, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, -1);
	glVertex3f(-1, 0, -1);
	glEnd();
	//END SURFACE REFLECT ----------------------------------------------
#pragma endregion surface
//START MODEL REFLECTION ----------------------------------------------

	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glPushMatrix();
	glScalef(0.1f, 0.1f, 0.1f);
	glScalef(1, -1, 1);
	glTranslatef(0, 10, 0);
	// rotation here
	policeCar.render();
	glPopMatrix();
	//END MODEL REFLECTION ----------------------------------------------

	//EVERYTHING BELOW IS REAL ----------------------------------------------

	//PHYSICAL SURFACE  ----------------------------------------------
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glColor4f(0.8f, 0.8f, 1.0f, 0.8f);

#pragma region surface
	glBegin(GL_QUADS);
	glVertex3f(-1, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, -1);
	glVertex3f(-1, 0, -1);
	glEnd();
	//glPopMatrix();
#pragma endregion surface
//PHYSICAL SURFACE END ----------------------------------------------
//LOAD ACTUAL MODEL ----------------------------------------------
	//glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glPushMatrix();
	glScalef(0.1f, 0.1f, 0.1f);
	glTranslatef(0, 10, 0);
	glRotatef(0, 0, 1, 0);
	policeCar.render();
	glPopMatrix();
	//END ACTUAL MODEL ----------------------------------------------
}

void Scene::AddReflections() {

//car reflection in colourful box

#pragma region carReflection
	//MAKE SURFACE REFLECT ----------------------------------------------
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // Turn off writing to the frame buffer
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1); //Set the stencil function to always pass
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); //replace values when the test passes
	glDisable(GL_DEPTH_TEST);
#pragma region surface
	glBegin(GL_QUADS);
	glVertex3f(1, 0, 50);
	glVertex3f(1, 4, 50);
	glVertex3f(6, 4, 50);
	glVertex3f(6, 0, 50);
	glEnd();
	//END SURFACE REFLECT ----------------------------------------------
#pragma endregion surface
//START MODEL REFLECTION ----------------------------------------------

	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); //rendering to the frame buffer
	glStencilFunc(GL_EQUAL, 1, 1); // stencil function to test if the value is 1
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //stencil operation to keep all values (we don’t want to change the stencil)

	glPushMatrix();
	glTranslatef(4, 1, 55);
	glScalef(0.5f, 0.5f, 0.5f);
	glScalef(1, 1, -1);
	glDisable(GL_DEPTH_TEST);
	policeCar.render();
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
	//END MODEL REFLECTION ----------------------------------------------

	//EVERYTHING BELOW IS REAL ----------------------------------------------
	//PHYSICAL SURFACE  ----------------------------------------------
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_BLEND); //Enable alpha blending (to combine the floor object with model)
	glDisable(GL_LIGHTING); //Disable lighting (100% reflective object)
	glColor4f(0.8f, 0.8f, 1.0f, 0.2f); //Set colour of wall object
#pragma region surface
	//Translate (this is where the model will render, distance should match)
	glBegin(GL_QUADS);
	glVertex3f(1, 0, 50);
	glVertex3f(1, 4, 50);
	glVertex3f(6, 4, 50);
	glVertex3f(6, 0, 50);
	glEnd();
#pragma endregion surface
	//PHYSICAL SURFACE END ----------------------------------------------
	//LOAD ACTUAL MODEL ----------------------------------------------
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glPushMatrix();
	glTranslatef(4, 1, 45);
	glScalef(0.5f, 0.5f, 0.5f);
	policeCar.render();
	glPopMatrix();
	//END ACTUAL MODEL ----------------------------------------------
#pragma endregion

	//render magic box
	magicBox.RenderMagicBox();
}

void Scene::AddModels(float dt) {
	material.ResetDefault();
	glEnable(GL_DEPTH_TEST);
	//MODEL - CAR
	glPushMatrix();
		if (carTimer > 0.005) {
			carTimer = 0;

			//travels to Z = 100 then travels back
			if (carDirection == "forward") {
				if (carDistance > 100) {
					carDirection = "backward";
				}
				carDistance += 0.2;
			}
			else {
				if (carDistance < 0) {
					carDirection = "forward";
				}
				carDistance -= 0.2;
			}
		}
		else{
			carTimer += dt;
		}

		glTranslatef(50, 0, carDistance);
		if (carDirection == "backward") {
			glRotatef(180, 0, 1, 0);
		}

		glScalef(2, 2, 2);
		policeCar.render();
	glPopMatrix();

	//MODEL - PERSON
	glPushMatrix();
		glTranslatef(5, 1, 10);
		person.render();
	glPopMatrix();

#pragma region Lamps
	
	//MODEL - LAMP
	glPushMatrix();
		glTranslatef(40, 0, 33);
		glScalef(0.1, 0.1, 0.1);
		lamp.render();
	glPopMatrix();

	//MODEL - LAMP 2
	glPushMatrix();
		glTranslatef(60, 0, 33);
		glScalef(0.1, 0.1, 0.1);
		lamp.render();
	glPopMatrix();

	//MODEL - LAMP 3
	glPushMatrix();
		glTranslatef(40, 0, 66);
		glScalef(0.1, 0.1, 0.1);
		lamp.render();
	glPopMatrix();

	//MODEL - LAMP 4
	glPushMatrix();
		glTranslatef(60, 0, 66);
		glScalef(0.1, 0.1, 0.1);
		lamp.render();
	glPopMatrix();

	//MODEL - LAMP 5
	glPushMatrix();
		glTranslatef(40, 0, 99);
		glScalef(0.1, 0.1, 0.1);
		lamp.render();
	glPopMatrix();

	//MODEL - LAMP 6
	glPushMatrix();
		glTranslatef(60, 0, 99);
		glScalef(0.1, 0.1, 0.1);
		lamp.render();
	glPopMatrix();

#pragma endregion

	//MODEL - BUILDNG2
	glPushMatrix();
		glTranslatef(90, 0, 10);
		glRotatef(90, 0, 1, 0);
		glScalef(0.01, 0.01, 0.01);
		building2.render();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(90, 0, 35);
		glRotatef(90, 0, 1, 0);
		glScalef(0.01, 0.01, 0.01);
		building2.render();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(90, 0, 60);
		glRotatef(90, 0, 1, 0);
		glScalef(0.01, 0.01, 0.01);
		building2.render();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(90, 0, 85);
		glRotatef(90, 0, 1, 0);
		glScalef(0.01, 0.01, 0.01);
		building2.render();
	glPopMatrix();

		//Get to the chopper
	glPushMatrix();
		glScalef(1, 1, 1);
		if (chopperHoverTimer > 0.005) {
			chopperHoverTimer = 0;
			chopperRotate += 0.4;
			
			if (chopperHoverDirection == "up" ) {
			
				choppeHoverDistance.y += 0.05;
				if (choppeHoverDistance.y > 25) {
					chopperHoverDirection = "down";
				}
			}
			else {
				choppeHoverDistance.y -= 0.05;

				if (choppeHoverDistance.y < 10) {
					chopperHoverDirection = "up";
				}
			
			}
		}
		else {
			chopperHoverTimer += dt;
		}
		glTranslatef(choppeHoverDistance.x, choppeHoverDistance.y, choppeHoverDistance.z);
		glScalef(2, 2, 2);
		glRotatef(chopperRotate, 0, 1, 0);
		helicopter.render();
	glPopMatrix();
}

void Scene::AddSkyBox() {
	
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		if (skyboxNum == 0) {
			AddTexture(skyBox1);
		}
		else if (skyboxNum == 1) {
			AddTexture(skyBox2);
		}
		else if (skyboxNum == 2) {
			AddTexture(skyBox3);
		}
		else if (skyboxNum == 3) {
			AddTexture(skyBox4);
		}
		
		glTranslatef(CurrentCameraPointer->GetCameraPosition().x, CurrentCameraPointer->GetCameraPosition().y, CurrentCameraPointer->GetCameraPosition().z);
		glTranslatef(-0.5, -0.5, -0.5);
		RenderCube();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	RemoveTexture();
}

void Scene::AddFloor() {
	material.SetEmission(0,0,0,1);
	material.SetDiffuse(0.5, 0.5, 0.5, 0.8);
	material.SetAmbient(0.8,0.8,0.8,0.8);
	material.SetShininess(1);

	//PLANE
	glPushMatrix();
		glEnable(GL_LIGHTING);
		glScalef(1, 1, 1);
		quadFloor.Render(100, 100);
	glPopMatrix();
	material.ResetDefault();
}

void Scene::AddShapes(float dt) {

	AddTexture(woodPlank);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//mad house
	material.ResetDefault();
	if (houseColourCurrentTimer > 0.5) {
		houseColourCurrentTimer = 0;

		houseEmissionSave[0] = std::rand() % 2;
		houseEmissionSave[1] = std::rand() % 2;
		houseEmissionSave[2] = std::rand() % 2;
		houseEmissionSave[3] = std::rand() % 1;
	}
	else {
		houseColourCurrentTimer += dt;
	}
	material.SetEmission(houseEmissionSave[0], houseEmissionSave[1], houseEmissionSave[2], houseEmissionSave[3]);
	material.SetDiffuse(std::rand() % 5 , std::rand() % 5 , std::rand() % 5 , std::rand() % 1);
	material.SetAmbient(std::rand() % std::rand() ,std::rand() % 5, std::rand() % 5, std::rand() % 5);
	material.SetShininess(std::rand() % 128);

	//wood house
	for (int i = 0; i < 5; i++) {
		//front
		PlaceCube(0, i, 50);
		PlaceCube(6, i, 50);

		//side left
		PlaceCube(6, i, 51);
		PlaceCube(6, i, 52);
		PlaceCube(6, i, 53);
		PlaceCube(6, i, 54);
		 
		//side right
		PlaceCube(0, i, 51);
		PlaceCube(0, i, 52);
		PlaceCube(0, i, 53);
		PlaceCube(0, i, 54);

		//back
		PlaceCube(1, i, 54);
		PlaceCube(2, i, 54);
		PlaceCube(3, i, 54);
		PlaceCube(4, i, 54);
		PlaceCube(5, i, 54);

		if (i == 4) {
			for (int width = 0; width < 5; width++) {
				for (int length = 0; length < 4; length++) {
					PlaceCube(1 + width, i, 50 + length);
				}
			}
		}
	}
	//RESET BUTTON
	material.ResetDefault();

	//sphere
	glPushMatrix();
		glTranslatef(5, 10, 10);
		sphere.RenderSphere();
	glPopMatrix();

	//WALL
	for (int i = 0; i < 100; i += 10) {
		glPushMatrix();
			if (i <= 0)
				AddTexture(woodPlank);
			else if (i <= 20)
				AddTexture(grass_texture);
			else if (i <= 40)
				AddTexture(red);
			else if(i <= 60)
				AddTexture(blue);
			else if (i <= 80)
				AddTexture(grass_texture);
			else if (i <= 100)
				AddTexture(woodPlank);

			glTranslatef(-1, 1, i);
			glRotatef(-90, 0, 1, 0);
			wall.Render(10, 10);
		glPopMatrix();
		RemoveTexture();
	}
	
	//moon
	AddTexture(moon);
	material.SetShininess(100);
	material.SetEmission(0.2, 0.2, 2, 1);
	material.SetDiffuse(0.2, 0.2, 2, 1);
	moonRotation += 60 * dt;
	glPushMatrix();
		glTranslatef(50, 60, 50);
		glRotatef(moonRotation, 0, 1, 1);
		glScalef(5, 5, 5);
		sphere.RenderSphere();

		//render second sphere
		glPushMatrix();
			glColor3f(1, 0.1, 0.1);
			glScalef(0.3, 0.3, 0.3);
			glRotatef(moonRotation * 1.2, 1, 0, 0);
			glTranslatef(0, 15, 15);
			sphere.RenderSphere();
		glPopMatrix();

		//render third sphere
		glPushMatrix();
			glColor3f(0.05, 0.3, 0.7);
			glScalef(0.3, 0.3, 0.3);
			glRotatef(-moonRotation * 2, 0, 0.7, 0.2);
			glTranslatef(0, 15, 15);
			sphere.RenderSphere();
		glPopMatrix();

		//render fourth sphere
		glPushMatrix();
			material.SetShininess(1);
			material.SetEmission(0, 0.5, 0,0.8);
			glColor3f(0.05, 0.3, 0.7);
			glScalef(0.4, 0.4, 0.4);
			glRotatef(-moonRotation * 0.7, 0.4, 0.2, 0.2);
			glTranslatef(5, 13, 13);
			sphere.RenderSphere();
		glPopMatrix();
	glPopMatrix();
		
	RemoveTexture();
	material.ResetDefault();

	//movable cube
	glColor3f(1, 0, 0);
	glPushMatrix();
		glTranslatef(moveableCubePos.x, moveableCubePos.y, moveableCubePos.z);
		glScalef(5, 5, 5);
		moveableCube.RenderCube();
	glPopMatrix();
}

void Scene::PlaceCube(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
		glTranslatef(x, y, z);
		cube.RenderCube();
	glPopMatrix();
}

void Scene::AddShadow() {

#pragma region lamps

	float lightPos[4] = { 50, 15, carDistance, 1 };
	float shadowMatrix[16];
	GLfloat floor[12] = {
	0,0.5,0, //bottom right
	0,0.5,100, //top right
	100,0.5,100, //top left
	100,0.5,0 //bottom left
	};
	//lamp 1
	float lampPos[4] = { 40,0,33 };
	LampShadowHelper((GLfloat*)shadowMatrix, lightPos, floor, lampPos);
	//lamp 2
	float newLampPos[4] = { 60,0,33 };
	std::copy(newLampPos, newLampPos + 3, lampPos); //copies new coords into lampPos array
	LampShadowHelper((GLfloat*)shadowMatrix, lightPos, floor, lampPos);
	//lamp 3
	float newLampPos2[4] = { 40,0,66 };
	std::copy(newLampPos2, newLampPos2 + 3, lampPos); //copies new coords into lampPos array
	LampShadowHelper((GLfloat*)shadowMatrix, lightPos, floor, lampPos);
	//lamp 4
	float newLampPos3[4] = { 60,0,66 };
	std::copy(newLampPos3, newLampPos3 + 3, lampPos); //copies new coords into lampPos array
	LampShadowHelper((GLfloat*)shadowMatrix, lightPos, floor, lampPos);
#pragma endregion

}

void Scene::LampShadowHelper(float* shadowMatrix, float lightPos[4], GLfloat floor[12], float lampPos[3]) {
	if (!isColourLighting) {
		glDisable(GL_LIGHTING); //cool effect when this is enabled
	}
	
	glDisable(GL_TEXTURE_2D);
	glColor4f(0.15f, 0.15f, 0.15f, 1); // Shadow's colour
	
	shadow1.generateShadowMatrix((GLfloat*)shadowMatrix, lightPos, floor);

	glPushMatrix();
		glMultMatrixf((GLfloat*)shadowMatrix);
			glTranslatef(lampPos[0], lampPos[1], lampPos[2]);
			glScalef(0.1f, 0.05f, 0.1f);
			lamp.render();
	glPopMatrix();

	glColor3f(1.0f, 1.0f, 1.0f); // S
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}

void Scene::MoveableCubeControls(float dt) {
	if (input->isKeyDown('u')) {
		moveableCubePos.y += dt * 3;
	}
	if (input->isKeyDown('h')) {
		moveableCubePos.x += dt * 3;
	}
	if (input->isKeyDown('j')) {
		moveableCubePos.y -= dt * 3;
	}
	if (input->isKeyDown('k')) {
		moveableCubePos.x -= dt * 3;
	}
}