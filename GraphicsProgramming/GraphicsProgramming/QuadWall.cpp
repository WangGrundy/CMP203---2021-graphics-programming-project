#include "QuadWall.h"

void QuadWall::Render(float x, float z) {

	int widthIncrease = 0;
	int heightIncrease = 0;

	glPushMatrix();
	for (int j = 0; j < z; j++) {
		for (int i = 0; i < x; i++) {
			
			glBegin(GL_QUADS);
			glNormal3f(0, 0, -1);
			glTexCoord2f(0, 0);
			glVertex3f(0 + widthIncrease, 0 + heightIncrease, 0);

			glNormal3f(0, 0, -1);
			glTexCoord2f(1, 0);
			glVertex3f(0 + widthIncrease, 1 + heightIncrease, 0);

			glNormal3f(0, 0, -1);
			glTexCoord2f(1, 1);
			glVertex3f(1 + widthIncrease, 1 + heightIncrease, 0);

			glNormal3f(0, 0, -1);
			glTexCoord2f(0, 1);
			glVertex3f(1 + widthIncrease, 0 + heightIncrease, 0);
			glEnd();

			widthIncrease += 1;
		}
		widthIncrease = 0;
		heightIncrease += 1;
	}
	glPopMatrix();

}