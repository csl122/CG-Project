// Shiliang Chen 20125016
#include "Swing.h"

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
Swing::Swing() : keyframe(-1), animateTime(0.0), animateRotation(0.0), animateTranslation(0.0),
interpA(0.0), interpB(0.0), sizeA(0.0), sizeB(0.0), interpTime(0.0) {}

/// Update the Swing position in releation to delta time by use of mathematical
/// mechanics, eq SUVAT
void Swing::Update(const double& deltaTime)
{
	// update the time and rotation steps
	animateTime += static_cast<float>(deltaTime);
	animateRotation += static_cast<float>(deltaTime);
	float g = 9.8f;
	float l = 8;
	float T = float(2 * PI * sqrt(l / g));

	sizeA = 30 * float(sin(g * (animateTime - T / 4) / l));



}

///Draw the Swing
void Swing::Display()
{
	// Always push before making any changes
	glPushMatrix();
	// Save current style attributes
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	// globally translate and scale
	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(-90, 0,1,0);

	DrawSwing();


	// Revert style attributes
	glPopAttrib();
	// pop matrix stack to revert to state prior to drawing
	glPopMatrix();
}


void Swing::drawCylinder(GLdouble r, GLdouble h)
{
	GLUquadricObj* cylinder;
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	cylinder = gluNewQuadric();
	gluCylinder(cylinder, r, r, h, 60, 1);
	glPopMatrix();

}

/// Draw a cube with normals
void Swing::DrawCube()
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


void Swing::DrawSwing()
{

	float angle = float(2 * PI / 36);
	glPushMatrix();

	// two strings
	glPushMatrix();

	glTranslatef(0, 550.f * float(cos(angle)) - 6.f, 0);

	glRotatef(sizeA, 1, 0, 0);
	//glRotatef(interpA + animateRotation * ((interpB - interpA) / interpTime), 1.0f, 0.0f, 0.0f);

	glColor3ub(150, 30, 30);
	glPushMatrix();
	glTranslatef(0, -415, 0);
	glScalef(85, 6, 30);
	DrawCube();
	glPopMatrix();

	glColor3ub(10, 10, 20);
	glPushMatrix();
	glTranslatef(-40, -415, 0);
	drawCylinder(0.5f, 415);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, -415, 0);
	drawCylinder(0.5f, 415);
	glPopMatrix();

	glPopMatrix();

	glColor3ub(240, 190, 0);
	// top two gadgets
	glPushMatrix();
	glColor3ub(240, 190, 0);
	glTranslatef(0, 550.f * float(cos(angle)), 0);

	glPushMatrix();
	glTranslatef(-40, -7.5, 0);
	glScalef(2, 13, 6);
	DrawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, -7.5, 0);
	glScalef(2, 13, 6);
	DrawCube();
	glPopMatrix();

	glPopMatrix();

	// top horizontal
	glPushMatrix();
	glColor3ub(240, 190, 0);
	glTranslatef(0, 550.f * float(cos(angle)) - 1.5f, 0);
	glRotatef(90, 0, 0, 1);
	glTranslatef(0, -203, 0);
	drawCylinder(3.f, 406);
	glPopMatrix();



	glPushMatrix();
	glTranslatef(-200, 0, 0);
	DrawSwingArm();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(200, 0, 0);
	DrawSwingArm();
	glPopMatrix();

	glPopMatrix();


}


void Swing::DrawSwingArm()
{
	float angle = float(2 * PI / 36);
	glPushMatrix();

	glPushMatrix();
	glColor3ub(240, 190, 0);
	glTranslatef(0, 550.f * float(cos(angle) / 4 * 3), 0);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, -550.f * float(sin(angle) / 4 * 1), 0);
	drawCylinder(3.f, 550.f * float(sin(angle) / 4 * 1 * 2));
	glPopMatrix();

	glPushMatrix();
	glColor3ub(60, 120, 130);
	glTranslatef(0, 550.f * float(cos(angle) / 3), 0);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, -550.f * float(sin(angle) / 3 * 2), 0);
	drawCylinder(3.f, 550.f * float(sin(angle) / 3 * 2 * 2));
	glPopMatrix();

	glTranslatef(0, 550.f * float(cos(angle)), 0);

	glPushMatrix();
	glRotatef(-10, 1, 0, 0);
	glTranslatef(0, -550.f, 0);
	glColor3ub(60, 120, 130);
	drawCylinder(3.f, 90.f);
	glTranslatef(0, 90.f, 0);
	glColor3ub(150, 30, 30);
	drawCylinder(3.f, 300.f);
	glTranslatef(0, 300.f, 0);
	glColor3ub(240, 190, 0);
	drawCylinder(3.f, 160.f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(10, 1, 0, 0);
	glTranslatef(0, -550.f, 0);
	glColor3ub(60, 120, 130);
	drawCylinder(3.f, 90.f);
	glTranslatef(0, 90.f, 0);
	glColor3ub(150, 30, 30);
	drawCylinder(3.f, 300.f);
	glTranslatef(0, 300.f, 0);
	glColor3ub(240, 190, 0);
	drawCylinder(3.f, 160.f);
	glPopMatrix();


	glPopMatrix();
}