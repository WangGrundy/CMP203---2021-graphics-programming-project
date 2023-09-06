#include "Reflection.h"

Reflection::Reflection() {
	if (!rose.load("models/rose/rose.obj", "models/rose/texture-green-paper-pattern-scratch-background-photo-hd-wallpaper.png")) {
		printf("Oh no. I can't load this file.");
	}
	if (!eye.load("models/eye/eyeball.obj", "models/eye/textures/eye.png")) {
		printf("Oh no. I can't load this file.");
	}
	if (!policeCar.load("models/Police_Car/PoliceCar.obj", "models/Police_Car/wiggu_vHoodNorm.bmp.png")) {
		printf("Oh no. I can't load this file.");
	}
}

void Reflection::RenderMagicBox() { //this a cube without the bottom

	////////////////////////////////////// FRONT ////////////////////////////////
#pragma region magicBox
	//MAKE SURFACE REFLECT ----------------------------------------------
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // Turn off writing to the frame buffer
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1); //Set the stencil function to always pass
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); //replace values when the test passes
	glDisable(GL_DEPTH_TEST);
#pragma region surface
	//front
	glBegin(GL_QUADS);
	glVertex3f(5, 0, 70);
	glVertex3f(5, 10, 70);
	glVertex3f(15, 10, 70);
	glVertex3f(15, 0, 70);

	//// //right
	//glVertex3f(5, 0, 80);
	//glVertex3f(5, 10, 80);
	//glVertex3f(5, 10, 70);
	//glVertex3f(5, 0, 70);
	glEnd();
	//back
	//END SURFACE REFLECT ----------------------------------------------
#pragma endregion surface
//START MODEL REFLECTION ----------------------------------------------

	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); //rendering to the frame buffer
	glStencilFunc(GL_EQUAL, 1, 1); // stencil function to test if the value is 1
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //stencil operation to keep all values (we don’t want to change the stencil)

	glPushMatrix();
	glTranslatef(10, 5, 73);
	glScalef(1, 1, -1);
	glRotatef(90, 0, 1, 0);
	policeCar.render();
	glPopMatrix();
	//END MODEL REFLECTION ----------------------------------------------

	//EVERYTHING BELOW IS REAL ----------------------------------------------
	//PHYSICAL SURFACE  ----------------------------------------------
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_BLEND); //Enable alpha blending (to combine the floor object with model)
	glDisable(GL_LIGHTING); //Disable lighting (100% reflective object)
	glColor4f(0.8f, 0.8f, 1.0f, 0.2f); //Set colour of wall object
#pragma region surface
	glBegin(GL_QUADS);
	glVertex3f(5, 0, 70);
	glVertex3f(5, 10, 70);
	glVertex3f(15, 10, 70);
	glVertex3f(15, 0, 70);

	////right
	//glVertex3f(5, 0, 80);
	//glVertex3f(5, 10, 80);
	//glVertex3f(5, 10, 70);
	//glVertex3f(5, 0, 70);
	glEnd();
#pragma endregion surface
	//PHYSICAL SURFACE END ----------------------------------------------
	//LOAD ACTUAL MODEL ----------------------------------------------
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glPushMatrix();
	glTranslatef(10, 5, 65);
	glScalef(0.5f, 0.5f, 0.5f);
	policeCar.render();
	glPopMatrix();
	//END ACTUAL MODEL ----------------------------------------------
#pragma endregion

////////////////////////////////// RIGHT ////////////////////////////////////////////////////////

#pragma region magicBox2
	//MAKE SURFACE REFLECT ----------------------------------------------
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // Turn off writing to the frame buffer
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1); //Set the stencil function to always pass
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); //replace values when the test passes
	glDisable(GL_DEPTH_TEST);
#pragma region surface
	glBegin(GL_QUADS);

	// //right
	glVertex3f(5, 0, 80);
	glVertex3f(5, 10, 80);
	glVertex3f(5, 10, 70);
	glVertex3f(5, 0, 70);
	glEnd();
	//back
	//END SURFACE REFLECT ----------------------------------------------
#pragma endregion surface
//START MODEL REFLECTION ----------------------------------------------

	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); //rendering to the frame buffer
	glStencilFunc(GL_EQUAL, 1, 1); // stencil function to test if the value is 1
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //stencil operation to keep all values (we don’t want to change the stencil)

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(10, 5, 75);
	glScalef(1, 1, -1);
	eye.render();
	glColor3f(1, 1, 1);
	glPopMatrix();
	//END MODEL REFLECTION ----------------------------------------------

	//EVERYTHING BELOW IS REAL ----------------------------------------------
	//PHYSICAL SURFACE  ----------------------------------------------
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_BLEND); //Enable alpha blending (to combine the floor object with model)
	glDisable(GL_LIGHTING); //Disable lighting (100% reflective object)
	glColor4f(0.8f, 0.8f, 1.0f, 0.2f); //Set colour of wall object
#pragma region surface
	glBegin(GL_QUADS);
	//right
	glVertex3f(5, 0, 80);
	glVertex3f(5, 10, 80);
	glVertex3f(5, 10, 70);
	glVertex3f(5, 0, 70);
	glEnd();
#pragma endregion surface
	//PHYSICAL SURFACE END ----------------------------------------------

#pragma endregion

////////////////////////////////// BACK ////////////////////////////////////////////////////////

#pragma region magicBox3
	//MAKE SURFACE REFLECT ----------------------------------------------
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // Turn off writing to the frame buffer
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1); //Set the stencil function to always pass
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); //replace values when the test passes
	glDisable(GL_DEPTH_TEST);
#pragma region surface
	//front
	glBegin(GL_QUADS);

	// back
	glVertex3f(5, 0, 80);
	glVertex3f(15, 0, 80);
	glVertex3f(15, 10, 80);
	glVertex3f(5, 10, 80);
	glEnd();
	//END SURFACE REFLECT ----------------------------------------------
#pragma endregion surface
//START MODEL REFLECTION ----------------------------------------------

	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); //rendering to the frame buffer
	glStencilFunc(GL_EQUAL, 1, 1); // stencil function to test if the value is 1
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //stencil operation to keep all values (we don’t want to change the stencil)

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(10, 0, 75);
	glScalef(0.1, 0.1, 0.1);
	rose.render();
	glPopMatrix();
	//END MODEL REFLECTION ----------------------------------------------

	//EVERYTHING BELOW IS REAL ----------------------------------------------
	//PHYSICAL SURFACE  ----------------------------------------------
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_BLEND); //Enable alpha blending (to combine the floor object with model)
	glDisable(GL_LIGHTING); //Disable lighting (100% reflective object)
	glColor4f(0.8f, 0.8f, 1.0f, 0.2f); //Set colour of wall object
#pragma region surface
	glBegin(GL_QUADS);
	//back
	glVertex3f(5, 0, 80);
	glVertex3f(15, 0, 80);
	glVertex3f(15, 10, 80);
	glVertex3f(5, 10, 80);
	glEnd();
#pragma endregion surface
	//PHYSICAL SURFACE END ----------------------------------------------

#pragma endregion

////////////////////////////////// LEFT ////////////////////////////////////////////////////////

#pragma region magicBox4
//MAKE SURFACE REFLECT ----------------------------------------------
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // Turn off writing to the frame buffer
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1); //Set the stencil function to always pass
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); //replace values when the test passes
	glDisable(GL_DEPTH_TEST);
#pragma region surface
	//front
	glBegin(GL_QUADS);

	//left
	glVertex3f(15, 0, 70);
	glVertex3f(15, 10, 70);
	glVertex3f(15, 10, 80);
	glVertex3f(15, 0, 80);
	glEnd();
	//END SURFACE REFLECT ----------------------------------------------
#pragma endregion surface
//START MODEL REFLECTION ----------------------------------------------

	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); //rendering to the frame buffer
	glStencilFunc(GL_EQUAL, 1, 1); // stencil function to test if the value is 1
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //stencil operation to keep all values (we don’t want to change the stencil)

	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(10, 5, 72);
	glScalef(3, 3, 3);
	cube2.RenderCube();
	glColor3f(1, 1, 1);
	glPopMatrix();
	//END MODEL REFLECTION ----------------------------------------------

	//EVERYTHING BELOW IS REAL ----------------------------------------------
	//PHYSICAL SURFACE  ----------------------------------------------
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_BLEND); //Enable alpha blending (to combine the floor object with model)
	glDisable(GL_LIGHTING); //Disable lighting (100% reflective object)
	glColor4f(0.8f, 0.8f, 1.0f, 0.2f); //Set colour of wall object
#pragma region surface
	glBegin(GL_QUADS);
	//left
	glVertex3f(15, 0, 70);
	glVertex3f(15, 10, 70);
	glVertex3f(15, 10, 80);
	glVertex3f(15, 0, 80);
	glEnd();
#pragma endregion surface
	//PHYSICAL SURFACE END ----------------------------------------------

#pragma endregion

////////////////////////////////// TOP ////////////////////////////////////////////////////////

#pragma region magicBox5
//MAKE SURFACE REFLECT ----------------------------------------------
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // Turn off writing to the frame buffer
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1); //Set the stencil function to always pass
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); //replace values when the test passes
	glDisable(GL_DEPTH_TEST);
#pragma region surface
	//front
	glBegin(GL_QUADS);

	//top
	glVertex3f(5, 10, 70);
	glVertex3f(5, 10, 80);
	glVertex3f(15, 10, 80);
	glVertex3f(15, 10, 70);
	glEnd();
	//END SURFACE REFLECT ----------------------------------------------
#pragma endregion surface
//START MODEL REFLECTION ----------------------------------------------

	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); //rendering to the frame buffer
	glStencilFunc(GL_EQUAL, 1, 1); // stencil function to test if the value is 1
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //stencil operation to keep all values (we don’t want to change the stencil)

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(10, 7, 75);
	glScalef(0.7, 0.7, 0.7);
	sphere2.RenderSphere();
	glColor3f(1, 1, 1);
	glPopMatrix();
	//END MODEL REFLECTION ----------------------------------------------

	//EVERYTHING BELOW IS REAL ----------------------------------------------
	//PHYSICAL SURFACE  ----------------------------------------------
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_BLEND); //Enable alpha blending (to combine the floor object with model)
	glDisable(GL_LIGHTING); //Disable lighting (100% reflective object)
	glColor4f(0.8f, 0.8f, 1.0f, 0.2f); //Set colour of wall object
#pragma region surface
	glBegin(GL_QUADS);
	//top
	glVertex3f(5, 10, 70);
	glVertex3f(5, 10, 80);
	glVertex3f(15, 10, 80);
	glVertex3f(15, 10, 70);
	glEnd();
#pragma endregion surface
	//PHYSICAL SURFACE END ----------------------------------------------
}