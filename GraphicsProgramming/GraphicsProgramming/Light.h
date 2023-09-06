#pragma once

#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Vector3.h"
#include <math.h>

class Light
{
public:
	Light(int lightNum);
	void Update();	
	bool isOn = true;

	//helper funcs
	void SetAmbient(GLfloat red, GLfloat blue, GLfloat green, GLfloat alpha);
	void SetDiffuse(GLfloat red, GLfloat blue, GLfloat green, GLfloat alpha);
	void SetPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat point);
	void SetSpotDirection(GLfloat x, GLfloat y, GLfloat z);
	void SetAttenuation(GLfloat constant, GLfloat linear, GLfloat exponential);
	void SetSpecular(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	void SetSpotCutOff(GLfloat distance);
	void SetIntensity(GLfloat intensity);
	void Enable();
	void Disable();
	GLfloat GetPositionX();
	GLfloat GetPositionY();
	GLfloat GetPositionZ();

	//RED,GREEN,BLUE,ALPHA //surround lighting
	GLfloat Light_Ambient[4] = { 0.1, 0.1, 0.1, 1.0f };

	//RED,GREEN,BLUE,ALPHA //colour of light given out
	GLfloat Light_Diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	//X, Y, Z, spotlight = (1)
	GLfloat Light_Position[4] = { 5.0f, 10.0f, 5.0f, 1.0f };

	//X, Y, Z  (NORMAL DIRECTION)
	GLfloat Spot_Direction[3] = { 0.0f, -1.0f, 0.0f };

	GLfloat Spot_Attenuation[3] = { 1.0, 0, 0 };
	GLfloat spotCutOff = 25;
	GLfloat intensity = 50; // [0, 128]

	//material like: 
	GLfloat Light_specular[4] = { 0.0, 0.0, 0.0, 1.0f }; //THIS SHIT NEEDS TO BE MOVED INTO MATERIALS FOR SHAPES.

	int lightNumber;
}; 

