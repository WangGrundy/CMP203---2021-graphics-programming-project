#pragma once

#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Vector3.h"
#include <math.h>

class Material
{
public:
	Material();
	void SetAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void SetDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void SetSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void SetShininess(GLfloat);
	void SetEmission(GLfloat, GLfloat, GLfloat, GLfloat);
	void ResetDefault();
	void Update();
protected:
	GLfloat no_mat[4] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat mat_ambient_colour[4] = { 0.8, 0.8, 0.2, 1.0 };

	GLfloat mat_diff_red[4] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat mat_diff_blue[4] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_diff_grey[4] = { 0.5, 0.5, 0.5, 1.0 };

	GLfloat mat_specular[4] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat no_shininess = 0.0;
	GLfloat low_shininess = 50;
	GLfloat high_shininess = 100;

	GLfloat mat_emission[4] = { 0.3, 0.2, 0.2, 0.0 };

	////////////////////////////////////////////
	GLfloat ambient[4] = { 0.2,0.2,0.2,1 };
	GLfloat diffuse[4] = { 0.8,0.8,0.8,1 };
	GLfloat specular[4] = { 0,0,0,1 };
	GLfloat shininess = 0;
	GLfloat emission[4] = { 0,0,0,1 };

	GLfloat ambient_default[4] = { 0.2,0.2,0.2,1 };
	GLfloat diffuse_default[4] = { 0.8,0.8,0.8,1 };
	GLfloat specular_default[4] = { 0,0,0,1 };
	GLfloat shininess_default = 0;
	GLfloat emission_default[4] = {0,0,0,1};
};

