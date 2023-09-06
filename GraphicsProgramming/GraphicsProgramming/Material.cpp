#include "Material.h"

Material::Material() {

}

void Material::Update() {
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMateriali(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
}

void Material::SetAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;
	Update();
}

void Material::SetDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;
	Update();
}

void Material::SetSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;
	Update();
}

void Material::SetShininess(GLfloat shine) {
	shininess = shine;
	Update();
}

void Material::SetEmission(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	emission[0] = r;
	emission[1] = g;
	emission[2] = b;
	emission[3] = a;
	Update();
}

void Material::ResetDefault() {
	for (int i = 0; i < 4; i++) {
		ambient[i] = ambient_default[i];
		diffuse[i] = diffuse_default[i];
		emission[i] = emission_default[i];
	}
	shininess = shininess_default;
	Update();
}