#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <vector>
#include "Vector3.h"
#include "Cube.h"
#include "Model.h"
#include "Sphere.h"

class Reflection
{
public:
	Reflection();
	void RenderMagicBox();
protected:
	Model policeCar, rose, eye;
	Cube cube2;
	Sphere sphere2;
};

