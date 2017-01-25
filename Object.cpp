#include "Object.h"
#include "Definitions.h"

game::Object::Object() {}

game::Object::~Object() {}

void game::Object::drawSphere(float tx, float ty, float tz,
				   float sx) {
	glPushMatrix();
	glTranslatef(tx, ty, tz);
	glScalef(sx, sx, sx);
	glutSolidSphere(1,10.,10.);
	glPopMatrix();
}

void game::Object::drawWall(float tx, float ty, float tz,
				   float sx, float sy, float sz) {
	glPushMatrix();
	glTranslatef(tx, ty, tz);
	glScalef(sx, sy, sz);
	glutSolidCube(1);
	glPopMatrix();
}