#include "Light.h"


Light::Light(const std::string& filename) : Light()
{
	texID = Scene::GetTexture(filename);

}

void Light::Display()
{

	
}

void Light::Update(const double& deltaTime)
{

	GLfloat light1_position[] = { 0.0, 1400.0, 200.0,1.0 };
	GLfloat spot_direction[] = { 0.0,0.0,1.0 };
	GLfloat light1_diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light1_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light1_ambient[] = { 0.2f,0.2f,0.2f,1.0 };
	GLfloat light2_position[] = { 0.0, 1400.0, -200.0,1.0 };
	GLfloat spot2_direction[] = { 0.0,0.0,-1.0 };

	// light 1 for spotlight in tunnel
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 50.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.5);

	// light 2 for spotlight in tunnel
	glLightfv(GL_LIGHT2, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 50.0);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot2_direction);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 1.5);

	glEnable(GL_LIGHTING);
	

	// light 0 global directional light
	GLfloat ambience0[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuse0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat specular0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat position0[] = { 0.0f, 1.0f, 0.2f, 0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambience0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);


	// light 3 scannning light
	GLfloat light3_position[] = { 0.0, 350.0, -1000.0,1.0 };
	GLfloat spot3_direction[] = { 0.0,-1.0,1.0 };
	GLfloat light3_diffuse[] = { 1.0,0.0,0.0,1.0 };
	GLfloat light3_specular[] = { 1.0,0.0,0.0,1.0 };
	GLfloat light3_ambient[] = { 0.2f,0.0f,0.0f,1.0 };


	glLightfv(GL_LIGHT3, GL_AMBIENT, light3_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light3_specular);
	glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 30.0);
	//glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot3_direction);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 10.5);//*/


}