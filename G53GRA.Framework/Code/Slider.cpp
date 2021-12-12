// Shiliang Chen 20125016
#include "Slider.h"

#include <cmath>
#include <math.h>
#define PI acos(-1)


/*
Linear interpolation between point A and B is used to decide where we are
between these two at time T.

NewPosition = startPosition + currentTime*[(distanceBetweenAandB)/totalTime];
or
NewPos = A + T*[(B-A)/totalTime]
(NewPos = interpA + animateRotation*[(interpB-interpA)/interpTime])

interpA is the position where the animation starts, in this case -15.
interpB is the position where it end, in this case -45.

interpTime is the total amount of time taken to move between the two
positions, in this case 1.75 seconds.

Then animateRotation keep track of the amount of time passed between starting
and ending the animation.
*/

// MAKE SURE WE INITIALISE OUR VARIABLES
Slider::Slider() : keyframe(-1), animateTime(0.0), animateRotation(0.0), animateTranslation(0.0),
interpA(0.0), interpB(0.0), sizeA(0.0), sizeB(0.0), interpTime(0.0) {}

/// Update the Slider position in releation to delta time by use of mathematical
/// mechanics, eq SUVAT
void Slider::Update(const double& deltaTime)
{
	// update the time and rotation steps
	animateTime += static_cast<float>(deltaTime);
	animateRotation += static_cast<float>(deltaTime);
	float g = 9.8f;
	float l = 8;
	float T = float(2 * PI * sqrt(l / g));

	sizeA = 30 * float(sin(g * (animateTime - T / 4) / l));



}

///Draw the Slider
void Slider::Display()
{
	// Always push before making any changes
	glPushMatrix();
	// Save current style attributes
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	// globally translate and scale
	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(-65, 0, 1, 0);

	DrawSlider();


	// Revert style attributes
	glPopAttrib();
	// pop matrix stack to revert to state prior to drawing
	glPopMatrix();
}


void Slider::drawCylinder(GLdouble r, GLdouble h)
{
	GLUquadricObj* cylinder;
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	cylinder = gluNewQuadric();
	gluCylinder(cylinder, r, r, h, 10, 1);
	glPopMatrix();

}

/// Draw a cube with normals
void Slider::DrawCube()
{
	// This function draws a unit cube centered around the origin

	glBegin(GL_QUADS);
	// Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	// Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	// Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	// Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	// Top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	// Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glEnd();
}

void Slider::DrawSlider()
{
	float angle = float(2 * PI / 36);
	//glTranslatef(0, -400.f, 0);
	glPushMatrix();

	DrawSliderPlatform();

	DrawSliderStair();

	DrawSliderSlider();

	glPopMatrix();
}

void Slider::DrawSliderPlatform()
{
	glPushMatrix();

	// column
	glPushMatrix();
	// red
	glColor3ub(150, 30, 30);
	drawCylinder(15.f, 300.f);
	glTranslatef(0, 300.f, 0);
	// green
	glColor3ub(60, 120, 130);
	drawCylinder(15.f, 90.f);
	glTranslatef(0, 90.f, 0);
	GLUquadricObj* cylinder;
	glRotatef(-90, 1, 0, 0);
	cylinder = gluNewQuadric();
	gluCylinder(cylinder, 15, 20, 10, 10, 1);
	glPopMatrix();

	// platform
	// yellow
	glColor3ub(240, 190, 0);
	glTranslatef(0, 400.f, 0);
	glPushMatrix();
	glScalef(150, 6, 150);
	DrawCube();
	glPopMatrix();

	//四条竖的
	glPushMatrix();
	glTranslatef(-72, 0.f, 72);
	drawCylinder(3, 80);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-72, 0.f, 52);
	drawCylinder(3, 80);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(72, 0.f, 72);
	drawCylinder(3, 80);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(72, 0.f, 52);
	drawCylinder(3, 80);
	glPopMatrix();

	// 长一点的两个横的
	glPushMatrix();
	glTranslatef(0, 40.f, 72);
	glRotatef(-90, 0, 0, 1);
	glTranslatef(0, -72.f, 0);
	drawCylinder(3, 144);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 77.f, 72);
	glRotatef(-90, 0, 0, 1);
	glTranslatef(0, -72.f, 0);
	drawCylinder(3, 144);
	glPopMatrix();

	//短的横的
	glPushMatrix();
	glTranslatef(72, 40.f, 62);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, -10.f, 0);
	drawCylinder(3, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(72, 77.f, 62);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, -10.f, 0);
	drawCylinder(3, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-72, 40.f, 62);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, -10.f, 0);
	drawCylinder(3, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-72, 77.f, 62);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, -10.f, 0);
	drawCylinder(3, 20);
	glPopMatrix();


	// platform

	// yellow
	glColor3ub(240, 190, 0);
	glRotatef(180, 0, 1, 0);

	//四条竖的
	glPushMatrix();
	glTranslatef(-72, 0.f, 72);
	drawCylinder(3, 80);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-72, 0.f, 52);
	drawCylinder(3, 80);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(72, 0.f, 72);
	drawCylinder(3, 80);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(72, 0.f, 52);
	drawCylinder(3, 80);
	glPopMatrix();

	// 长一点的两个横的
	glPushMatrix();
	glTranslatef(0, 40.f, 72);
	glRotatef(-90, 0, 0, 1);
	glTranslatef(0, -72.f, 0);
	drawCylinder(3, 144);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 77.f, 72);
	glRotatef(-90, 0, 0, 1);
	glTranslatef(0, -72.f, 0);
	drawCylinder(3, 144);
	glPopMatrix();

	//短的横的
	glPushMatrix();
	glTranslatef(72, 40.f, 62);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, -10.f, 0);
	drawCylinder(3, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(72, 77.f, 62);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, -10.f, 0);
	drawCylinder(3, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-72, 40.f, 62);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, -10.f, 0);
	drawCylinder(3, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-72, 77.f, 62);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, -10.f, 0);
	drawCylinder(3, 20);
	glPopMatrix();



	glPopMatrix();
}

void Slider::DrawSliderStair()
{
	glPushMatrix();
	glDisable(GL_CULL_FACE);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(50.f, 403.f, 55.f);
	glVertex3f(453.f, 0.f, 55.f);
	glVertex3f(493.f, 0.f, 55.f);
	glVertex3f(90.f, 403.f, 55.f);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(50.f, 403.f, -55.f);
	glVertex3f(453.f, 0.f, -55.f);
	glVertex3f(493.f, 0.f, -55.f);
	glVertex3f(90.f, 403.f, -55.f);
	glEnd();

	glEnable(GL_CULL_FACE);

	glTranslatef(73, 400.f, 0);
	glColor3ub(30, 50, 100);
	for (size_t i = 1; i < 16; i++)
	{
		glTranslatef(25, -25.f, 0);
		glPushMatrix();
		glScalef(38, 3, 109);
		DrawCube();
		glPopMatrix();
	}
	glPopMatrix();
}

void Slider::DrawSliderSlider()
{
	glPushMatrix();
	glColor3ub(60, 120, 130);
	glDisable(GL_CULL_FACE);
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-75.f, 425.f, 55.f);
	glVertex3f(-90.f, 425.f, 55.f);
	glVertex3f(-100.f, 420.f, 55.f);
	glVertex3f(-105.f - 380 * float(sqrt(3)), 25.f, 55.f);
	glVertex3f(-100.f - 380 * float(sqrt(3)), 0.f, 55.f);
	glVertex3f(-90, 397.f, 55.f);
	glVertex3f(-75, 397.f, 55.f);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-105.f - 380 * float(sqrt(3)), 25.f, 55.f);
	glVertex3f(-855, 25.f, 55.f);
	glVertex3f(-855, 0.f, 55.f);
	glVertex3f(-100.f - 380 * float(sqrt(3)), 0.f, 55.f);
	glEnd();

	glPushMatrix();
	glTranslatef(0, 0, -110);
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-75.f, 425.f, 55.f);
	glVertex3f(-90.f, 425.f, 55.f);
	glVertex3f(-100.f, 420.f, 55.f);
	glVertex3f(-105.f - 380 * float(sqrt(3)), 25.f, 55.f);
	glVertex3f(-100.f - 380 * float(sqrt(3)), 0.f, 55.f);
	glVertex3f(-90, 397.f, 55.f);
	glVertex3f(-75, 397.f, 55.f);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-105.f - 380 * float(sqrt(3)), 25.f, 55.f);
	glVertex3f(-855, 25.f, 55.f);
	glVertex3f(-855, 0.f, 55.f);
	glVertex3f(-100.f - 380 * float(sqrt(3)), 0.f, 55.f);
	glEnd();
	glPopMatrix();

	glColor3ub(30, 50, 100);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(-75, 397.f, 55.f);
	glVertex3f(-75, 397.f, -55.f);
	glVertex3f(-90, 397.f, 55.f);
	glVertex3f(-90, 397.f, -55.f);
	glVertex3f(-100.f - 380 * float(sqrt(3)), 0.f, 55.f);
	glVertex3f(-100.f - 380 * float(sqrt(3)), 0.f, -55.f);
	glVertex3f(-855, 0.f, 55.f);
	glVertex3f(-855, 0.f, -55.f);

	glEnd();

	glEnable(GL_CULL_FACE);

	glPopMatrix();
}
