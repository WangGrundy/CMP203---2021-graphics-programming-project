#include "Light.h"


Light::Light(int lightNum) {

	lightNumber = lightNum;

	glLightf(lightNumber, GL_CONSTANT_ATTENUATION, Spot_Attenuation[0]);
	glLightf(lightNumber, GL_LINEAR_ATTENUATION, Spot_Attenuation[1]);
	glLightf(lightNumber, GL_QUADRATIC_ATTENUATION, Spot_Attenuation[2]);

	glLightfv(lightNumber, GL_DIFFUSE, Light_Diffuse);
	glLightfv(lightNumber, GL_POSITION, Light_Position);
	glLightfv(lightNumber, GL_AMBIENT, Light_Ambient);
	glLightfv(lightNumber, GL_SPOT_DIRECTION, Spot_Direction);
	glLightf(lightNumber, GL_SPOT_CUTOFF, spotCutOff);
	glLightf(lightNumber, GL_SPOT_EXPONENT, intensity); //  [0, 128]
	glLightfv(lightNumber, GL_SPECULAR, Light_specular);
}

void Light::Update() {
	glLightf(lightNumber, GL_CONSTANT_ATTENUATION, Spot_Attenuation[0]);
	glLightf(lightNumber, GL_LINEAR_ATTENUATION, Spot_Attenuation[1]);
	glLightf(lightNumber, GL_QUADRATIC_ATTENUATION, Spot_Attenuation[2]);

	glLightfv(lightNumber, GL_DIFFUSE, Light_Diffuse);
	glLightfv(lightNumber, GL_POSITION, Light_Position);
	glLightfv(lightNumber, GL_AMBIENT, Light_Ambient);
	glLightfv(lightNumber, GL_SPOT_DIRECTION, Spot_Direction);
	glLightf(lightNumber, GL_SPOT_CUTOFF, spotCutOff);
	glLightf(lightNumber, GL_SPOT_EXPONENT, intensity); //  [0, 128]
	glLightfv(lightNumber, GL_SPECULAR, Light_specular);
}

void Light::SetAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	Light_Ambient[0] = r;
	Light_Ambient[1] = g;
	Light_Ambient[2] = b;
	Light_Ambient[3] = a;
}

void Light::SetDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	Light_Diffuse[0] = r;
	Light_Diffuse[1] = g;
	Light_Diffuse[2] = b;
	Light_Diffuse[3] = a;
}

void Light::SetPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat spotlight) {
	Light_Position[0] = x;
	Light_Position[1] = y;
	Light_Position[2] = z;
	Light_Position[3] = spotlight;
}

void Light::SetSpotDirection(GLfloat x, GLfloat y, GLfloat z) {
	Spot_Direction[0] = x;
	Spot_Direction[1] = y;
	Spot_Direction[2] = z;
}

void Light::Enable() {
	glEnable(lightNumber);
}

void Light::Disable() {
	glDisable(lightNumber);
}

GLfloat Light::GetPositionX()
{
	return Light_Position[0];
}
GLfloat Light::GetPositionY() {
	return Light_Position[1];
}
GLfloat Light::GetPositionZ() {
	return Light_Position[2];
}

void Light::SetAttenuation(GLfloat constant, GLfloat linear, GLfloat exponential) {
	Spot_Attenuation[0] = constant;
	Spot_Attenuation[1] = linear;
	Spot_Attenuation[2] = exponential;
}

void Light::SetSpotCutOff(GLfloat distance) {
	spotCutOff = distance;
}

void Light::SetIntensity(GLfloat setintensity) {
	intensity = setintensity;
}

void Light::SetSpecular(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	Light_specular[0] = red;
	Light_specular[1] = blue;
	Light_specular[2] = green;
	Light_specular[3] = alpha;
}