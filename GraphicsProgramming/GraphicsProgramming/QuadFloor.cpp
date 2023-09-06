#include "QuadFloor.h"

void QuadFloor::Render(float x, float z) {

	int widthIncrease = 0;
	int heightIncrease = 0;
	
	glPushMatrix();
	for (int j = 0; j < z; j++) {
		for (int i = 0; i < x; i++) {
			glNormal3f(0, 1, 0);
			if (i < 40 || i > 60 ) { //ground
				glColor3f(0.5, 1.0, 0.2);
			}
			else { //road
				glColor3f(0.2, 0.2, 0.2);	
			}

			glBegin(GL_QUADS);
				glVertex3f(0 + widthIncrease, 0, 0 + heightIncrease);
				glVertex3f(0 + widthIncrease, 0, 1 + heightIncrease);
				glVertex3f(1 + widthIncrease, 0, 1 + heightIncrease);
				glVertex3f(1 + widthIncrease, 0, 0 + heightIncrease);
			glEnd();

			widthIncrease += 1;
		}
		widthIncrease = 0;
		heightIncrease += 1;
	}
	glPopMatrix();

	glColor3f(1, 1, 1);
}
