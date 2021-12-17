#include "TimeTunnel.h"
#include "Head.h"


TimeTunnel::TimeTunnel(const std::string& filename) : TimeTunnel()
{
	texID = Scene::GetTexture(filename);

}

void TimeTunnel::Display()
{

	glColor3ub(255, 255, 255);


	glEnable(GL_TEXTURE_2D);

	glDisable(GL_CULL_FACE);
	// ceil
	glBindTexture(GL_TEXTURE_2D, Scene::GetTexture("./Textures/sky.bmp"));
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1100, 600.f, -1100);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1100, 600.f, 1100);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1100, 600.f, 1100);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1100, 600.f, -1100);
	glEnd();
	glEnable(GL_CULL_FACE);

	// prompt board
	glBindTexture(GL_TEXTURE_2D, Scene::GetTexture("./Textures/prompt.bmp"));
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(220.f, 1400.f, 600.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(220.f, 1250.f, 600.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(20.f, 1250.f, 600.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(20.f, 1400.f, 600.0f);
	glEnd();

	// move board
	glBindTexture(GL_TEXTURE_2D, Scene::GetTexture("./Textures/move.bmp"));
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-20.f, 1400.f, 600.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-20.f, 1250.f, 600.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-220.f, 1250.f, 600.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-220.f, 1400.f, 600.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texID);
	glPushMatrix();
	glTranslatef(0.f, 1250.f, -600.f);
	GLUquadricObj* y = gluNewQuadric();
	gluQuadricOrientation(y, GLU_INSIDE);
	gluQuadricDrawStyle(y, GLU_FILL);
	gluQuadricNormals(y, GLU_SMOOTH);
	gluQuadricTexture(y, GL_TRUE);
	gluCylinder(y, 150.f, 300.f, 1200.f, 32, 32);
	gluDeleteQuadric(y);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void TimeTunnel::Update(const double& deltaTime)
{

	if (!Head::_flagStart)
	{
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
	}

}