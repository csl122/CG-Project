#include "Doors.h"
#define PI acos(-1)


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
	// circle
	glPushMatrix();
	glTranslatef(-300, 0, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(60, 60, 60);
	glDisable(GL_CULL_FACE);
	glColor3ub(60, 120, 130);
	float h = 0.25;
	float scale = 0.7;

	// outside circle
	glBegin(GL_QUAD_STRIP);
	int i = 0;
	for (i = 360; i >= 0; i -= 15)
	{
		float p = i * PI / 180;
		float x = float(sin(p));
		float z = float(cos(p));
		glNormal3f(x, h, z);
		glVertex3f(x, h, z);
		glNormal3f(x, 0.0f, z);
		glVertex3f(x, 0.0f, z);

		
	}
	glEnd();

	// inside circle
	glBegin(GL_QUAD_STRIP);
	i = 0;
	for (i = 360; i >= 0; i -= 15)
	{
		float p = i * PI / 180;
		float x = float(sin(p));
		float z = float(cos(p));

		// inner
		glNormal3f(-scale * x, -h, -scale * z);
		glVertex3f(scale * x, h, scale * z);
		glNormal3f(-scale * x, 0.0f, -scale * z);
		glVertex3f(scale * x, 0.0f, scale * z);
	}
	glEnd();

	// upper surface
	glBegin(GL_QUAD_STRIP);
	i = 0;
	for (i = 360; i >= 0; i -= 15)
	{
		float p = i * PI / 180;
		float x = float(sin(p));
		float z = float(cos(p));

		glNormal3f(0, 1, 0);
		glVertex3f(scale * x, h, scale * z);
		glNormal3f(0, 1, 0);
		glVertex3f(1 * x, h, 1 * z);
	}
	glEnd();

	glEnable(GL_CULL_FACE);
	glPopMatrix();



}