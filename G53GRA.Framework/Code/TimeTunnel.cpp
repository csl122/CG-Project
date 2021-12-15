#include "TimeTunnel.h"


TimeTunnel::TimeTunnel(const std::string& filename) : TimeTunnel()
{
	texID = Scene::GetTexture(filename);

}

void TimeTunnel::Display()
{

	glColor3ub(255, 255, 255);

	glutSolidCube(3);

	glEnable(GL_TEXTURE_2D);

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
	//float ambient[4], diffuse[4], specular[4]; // member variables for the reflectance model parameters
	//ambient[0] = 0.2f;    // Set the ambient colour of the light
	//ambient[1] = 0.2f;
	//ambient[2] = 0.2f;
	//ambient[3] = 1.0f;

	//diffuse[0] = 1.f;    // Set the diffuse colour of the light
	//diffuse[1] = 1.f;
	//diffuse[2] = 1.f;
	//diffuse[3] = 1.0f;

	//specular[0] = 1.0f;   // Set the specular colour of the light
	//specular[1] = 1.0f;
	//specular[2] = 1.0f;
	//specular[3] = 1.0f;

	//float spot_direction[3] = {-1., -1., 1.0};

	//// turn lighting on
	//glEnable(GL_LIGHTING);

	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	//glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15.0);
	//
	//// pass openGL the lighting model parameters for the Phong reflection model
	//glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	//glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 2);

	//float ldirection[] = { 500.f, 500.f, -500.f, 1.0f };
	//glLightfv(GL_LIGHT1, GL_POSITION, ldirection);

	//// enable light 1
	//glEnable(GL_LIGHT1);

	GLfloat light1_position[] = { 0.0, 1400.0, 200.0,1.0 };
	GLfloat spot_direction[] = { 0.0,0.0,1.0 };
	GLfloat light1_diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light1_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light1_ambient[] = { 0.2f,0.2f,0.2f,1.0 };
	GLfloat light2_position[] = { 0.0, 1400.0, -200.0,1.0 };
	GLfloat spot2_direction[] = { 0.0,0.0,-1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 50.0);//角度
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);//方向
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.5);//*/

	glLightfv(GL_LIGHT2, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
	//glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.5);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 50.0);//角度
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot2_direction);//方向
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 1.5);//*/

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);


	GLfloat ambience0[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuse0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat specular0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat position0[] = { 0.0f, 1.0f, 0.2f, 0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambience0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);


	
	GLfloat light3_position[] = { 0.0, 350.0, -1000.0,1.0 };
	GLfloat spot3_direction[] = { 0.0,-1.0,1.0 };
	GLfloat light3_diffuse[] = { 1.0,0.0,0.0,1.0 };
	GLfloat light3_specular[] = { 1.0,0.0,0.0,1.0 };
	GLfloat light3_ambient[] = { 0.2f,0.0f,0.0f,1.0 };


	glLightfv(GL_LIGHT3, GL_AMBIENT, light3_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light3_specular);
	glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 30.0);//角度
	//glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot3_direction);//方向
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 10.5);//*/


}