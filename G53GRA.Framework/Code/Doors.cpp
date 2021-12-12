#include "Doors.h"


Doors::Doors(const std::string& filename) : Doors()
{
	texID = Scene::GetTexture(filename);
}

void Doors::Display()
{
	glPushMatrix();
	// Save current style attributes
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	// Set colour to pale grey
	glColor3ub(250, 250, 250);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);

	DrawDoors();

	// Revert style attributes
	glPopAttrib();
	glPopMatrix();
}

void Doors::drawCylinder(GLdouble r, GLdouble h)
{
	GLUquadricObj* cylinder;
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	cylinder = gluNewQuadric();
	gluCylinder(cylinder, r, r, h, 10, 1);
	glPopMatrix();

}

void Doors::DrawDoors()
{
	glPushMatrix();
	glDisable(GL_CULL_FACE);
	
	glBegin(GL_QUAD_STRIP);//连续填充四边形串
	int i = 0;
	for (i = 390; i >= 0; i -= 15)
	{
		float p = i * 3.14 / 180;
		glVertex3f(sin(p), cos(p), 1.0f);
		glVertex3f(sin(p), cos(p), 0.0f);
	}
	glEnd();

	glEnable(GL_CULL_FACE);
	glPopMatrix();
}