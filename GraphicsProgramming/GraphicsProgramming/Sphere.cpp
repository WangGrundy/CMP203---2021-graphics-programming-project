#include "Sphere.h"

# define M_PI           3.14159265358979323846

void Sphere::RenderSphere() {

	float segments = 20;
	float theta = 2 * M_PI / segments; //lat
	float delta = M_PI / segments; //long
	float r = 3;
	float X, Y, Z;
	float latitude = 0, longitude = 0;

	glBegin(GL_QUADS);
	for (int i = 0; i < segments; i++) {
		for (int j = 0; j < segments; j++) {
			X = r * cosf(latitude) * sinf(longitude);
			Y = r * cosf(longitude);
			Z = r * sinf(latitude) * sinf(longitude);
			glNormal3f(X, Y, Z);
			glTexCoord2f(0, 0);
			glVertex3f(X, Y, Z);

			X = r * cosf(latitude + theta) * sinf(longitude);
			Y = r * cosf(longitude);
			Z = r * sinf(latitude + theta) * sinf(longitude);
			glNormal3f(X, Y, Z);
			glTexCoord2f(0, 1);
			glVertex3f(X, Y, Z);

			X = r * cosf(latitude + theta) * sinf(longitude + delta);
			Y = r * cosf(longitude + delta);
			Z = r * sinf(latitude + theta) * sinf(longitude + delta);
			glNormal3f(X, Y, Z);
			glTexCoord2f(1, 1);
			glVertex3f(X, Y, Z);

			X = r * cosf(latitude) * sinf(longitude + delta);
			Y = r * cosf(longitude + delta);
			Z = r * sinf(latitude) * sinf(longitude + delta);
			glNormal3f(X, Y, Z);
			glTexCoord2f(1, 0);
			glVertex3f(X, Y, Z);
			latitude += theta;
		}
		latitude = 0.f;
		longitude += delta;
	}
	glEnd();
}

