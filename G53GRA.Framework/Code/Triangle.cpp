#include "Triangle.h"
#include <iostream>
using namespace std;

/// initalise the triangles properties
Triangle::Triangle() : xrot(0.0f), yrot(0.0f), zrot(0.0f), scale(0.5f){}

/// draw the triangle in the scene
void Triangle::Display()
{
	glPushMatrix();

	glTranslatef(0.0f, 1250.0f, -600.0f);

	// rotate the triangle by the given degrees
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);

	// scale the traingle
	glScalef(0.75f, 0.75f, 0.75f);

	glTranslatef(0.0f, -150.0f, 00.0f);

	// disable culling (removal) of backface triangles so that when we look at
	// triangle to does not disappearthe back of the
	glDisable(GL_CULL_FACE);

	// draw the triangle us GL_TRIANGLES as the primative so that every 3
	// joined into one triangle verticies we pass get
	glBegin(GL_QUADS);

	// set the colour of the first vertex (8-bit RGB)
	glColor3ub(3, 70, 174); // [3ub] unsigned byte x 3 = 0-255
	// set the position of the first vertex
	glVertex3f(-400.0f, -400.0f, 0.0);

	// set the colour of the second vertex (normalised RGB)
	glColor3ub(10.f, 207.0f, 226.0f); // [3f] float x 3 = 0.0f-1.0f
	// set the position of the second vertex
	glVertex3f(400.0f, -400.0f, 0.0f);

	// set the colour of the third vertex (normalised RGBA)
	glColor3ub(166.0f, 170.0f, 253.0f); // [4f] float x 4 = 0.0f-1.0f
	// set the position of the third vertex
	glVertex3f(400.0f, 400.0f, 0.0f);

	// set the colour of the third vertex (normalised RGBA)
	glColor3ub(90.0f, 9.0f, 156.0f); // [4f] float x 4 = 0.0f-1.0f
	// set the position of the third vertex
	glVertex3f(-400.0f, 400.0f, 0.0f);

	// stop drawing triangles
	glEnd();

	// re-enable face culling for other objects in the scene
	glEnable(GL_CULL_FACE);

	// revert back to the matrix we had before we added the triangles transforms 
	// in the scene are not effected by the triangles transformations so that 
	// other objects 
	glPopMatrix();
}

/// update the Z rotation variable with change in time
void Triangle::Update(const double& deltaTime)
{
	zrot += 30.0f * static_cast<float>(deltaTime);

	//float x, y, z;
	//Camera* camera = Scene::GetCamera();
	//camera->GetEyePosition(x, y, z);
	//
	//if (abs(x - 0) < 200 && abs(z - (-570)) < 10 && abs(y - (1350)) < 10)
	//{
	//	//camera->Reset();
	//	camera->SetCameraPosition(0.f, 50.f, 935.f); //(0.f ,50.f, 935.f)(0., 1350.0f, 500.)
	//}
}

/// set scale variables based on a key press
void Triangle::HandleKey(unsigned char key, int state, int x, int y)
{
	switch (key)
	{
		case 'i':
			scale += 0.1f;
			break;
		case 'k':
			scale -= 0.1f;
			break;
		default:
			break;
	}
}
