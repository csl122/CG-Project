#include "Turntable.h"

#include <cmath>
#include <math.h>
#define PI acos(-1)

// define a gravity constance for the bounce equation
#define GRAVITY -9.8f

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
Turntable::Turntable() : keyframe(-1), animateTime(0.0), animateRotation(0.0), animateTranslation(0.0), _flagAnimation(true),
interpA(0.0), interpB(0.0), sizeA(0.0), sizeB(0.0), interpTime(0.0) {}

/// Update the lamps position in releation to delta time by use of mathematical
/// mechanics, eq SUVAT
void Turntable::Update(const double& deltaTime)
{
	if (_flagAnimation) {
		// update the time and rotation steps
		animateTime += static_cast<float>(deltaTime);
		animateRotation += static_cast<float>(deltaTime);

		// check if we hit the end of the animation (3 seconds), if so reset
		if (animateTime >= 7.0f)
		{
			animateTime = 0.0f;
			keyframe = -1;
		}

		// check if we are in the 1st second of animation
		if (animateTime < 7.f)
		{
			// check if we have only just entered the 1st keyframe in which case
			// set up the parameters
			if (keyframe != 0)
			{
				animateTime = 0.0f;
				animateRotation = 0.0f;
				animateTranslation = 0.0f;
				keyframe = 0;
				interpA = 0.0f;
				interpB = 360.0f;
				sizeA = 3.0f;
				sizeB = 1.5f;
				interpTime = 7.f;
			}
		}
	}

}

///Draw the lamp
void Turntable::Display()
{
	// Always push before making any changes
	glPushMatrix();

	// Save current style attributes
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	// Set colour to pale grey
	glColor3ub(250, 250, 250);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);


	glScalef(20, 20, 20);

	glRotatef(interpA + animateRotation * ((interpB - interpA) / interpTime), 0.0f, 1.0f, 0.0f);
	drawTurntable();

	// Revert style attributes
	glPopAttrib();

	// pop matrix stack to revert to state prior to drawing
	glPopMatrix();
}

void Turntable::drawTurntable()
{
	// The cylinder base without top circle
	glPushMatrix();
	glScalef(3, 3, 3);
	glTranslatef(0.f, -0.065f, 0.f);
	glColor3ub(246, 226, 171);
	drawCylinder(0.48, 0.055);

	// The top cicle with two colours
	glTranslatef(0.f, 0.05f, 0.f);
	Circle(0.48f);
	glPopMatrix();

	// The middle cylinder
	glColor3ub(255, 168, 185);
	drawCylinder(0.1, 4.55f);

	// small ball on the top of middle cylinder
	glPushMatrix();
	glColor3ub(255, 100, 100);
	glTranslatef(0, 4.55f, 0);
	glutSolidSphere(0.23, 10, 10);
	glPopMatrix();

	// four cylinder arms
	glPushMatrix();

	glColor3ub(240, 190, 0);
	CurvedCylinder(0.07f / 5, 5.5f);
	glRotatef(45, 0, 1, 0);
	glColor3ub(60, 120, 130);
	CurvedCylinder(0.07f / 5, 5.5f);
	glRotatef(45, 0, 1, 0);
	glColor3ub(150, 30, 30);
	CurvedCylinder(0.07f / 5, 5.5f);
	glRotatef(45, 0, 1, 0);
	glColor3ub(60, 120, 130);
	CurvedCylinder(0.07f / 5, 5.5f);
	glRotatef(45, 0, 1, 0);
	glColor3ub(240, 190, 0);
	CurvedCylinder(0.07f / 5, 5.5f);
	glRotatef(45, 0, 1, 0);
	glColor3ub(60, 120, 130);
	CurvedCylinder(0.07f / 5, 5.5f);
	glRotatef(45, 0, 1, 0);
	glColor3ub(150, 30, 30);
	CurvedCylinder(0.07f / 5, 5.5f);
	glRotatef(45, 0, 1, 0);
	glColor3ub(60, 120, 130);
	CurvedCylinder(0.07f / 5, 5.5f);

	glPopMatrix();

	// four horses~
	glPushMatrix();
	glColor3ub(150, 30, 30);
	glPushMatrix();
	glTranslatef((GLfloat)-sqrt(1.5), 0.f, 0.f);
	drawHorse();
	glPopMatrix();
	glColor3ub(240, 190, 0);
	glPushMatrix();
	glTranslatef((GLfloat)sqrt(1.5), 0.f, 0.f);
	drawHorse();
	glPopMatrix();
	glColor3ub(60, 120, 130);
	glPushMatrix();
	glTranslatef(0, 0.f, (GLfloat)sqrt(1.5));
	glRotatef(-90, 0, 1, 0);
	drawHorse();
	glPopMatrix();
	glColor3ub(60, 120, 130);
	glPushMatrix();
	glTranslatef(0.f, 0.f, (GLfloat)-sqrt(1.5));
	glRotatef(-90, 0, 1, 0);
	drawHorse();
	glPopMatrix();

	glPopMatrix();
}

void Turntable::drawHorse()
{
	glPushMatrix();

	glPushMatrix();
	glTranslatef(0.f, 2.97f, 0.53f);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(0.03, 1.06);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, 0.f, 0.5f);
	drawCylinder(0.03, 3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, 0.f, -0.5f);
	drawCylinder(0.03, 3);
	glPopMatrix();


	glPopMatrix();
}

void Turntable::Circle(float r)
{
	glPushMatrix();
	glScalef(r, 1, r);
	glRotatef(90, 1, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, 0.0f);
	int i = 0;
	for (i = 0; i <= 360; i += 6)
	{
		if (i == 0 || i == 180)
		{
			glColor3ub(255, 200, 200);
		}
		else if (i == 90 || i == 270)
		{
			glColor3ub(170, 170, 255);
		}
		GLfloat p = i * (GLfloat)PI / 180.f;
		glVertex3f(sin(p), cos(p), 0.0f);
	}
	glEnd();
	glPopMatrix();
}


void Turntable::drawCylinder(GLdouble r, GLdouble h)
{
	GLUquadricObj* cylinder;
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);

	cylinder = gluNewQuadric();

	gluCylinder(cylinder, r, r, h, 10, 1);
	glPopMatrix();

}


/// Draw a cube with normals
void Turntable::DrawCube()
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




void Turntable::CurvedCylinder(GLfloat radius, GLfloat height)
{
	glPushMatrix();
	glTranslatef(0.1f, 2.f, 0);
	glRotatef(-72, 0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glScalef(5, 5, 5);
	GLfloat w0, w1, ang0, ang1, angle, x, y, xb, yb, zb;
	int i, j;

	int     slices = 18;
	GLfloat bend_radius = 0.5f;

	GLfloat bend_angle, bend_ang0, bend_ang1;

	bend_angle = bend_radius * height;
	bend_ang0 = -bend_angle / 2.0f;
	bend_ang1 = bend_angle / 2.0f;

	for (i = 0; i < slices; i++)
	{
		w0 = (float)i / (float)slices;
		w1 = (float)(i + 1) / (float)slices;

		ang0 = bend_ang0 + (bend_ang1 - bend_ang0) * w0;
		ang1 = bend_ang0 + (bend_ang1 - bend_ang0) * w1;

		//glColor3ub(247, 208, 155);
		//glColor3f(1.0f - w0, 0.0, w1);
		glBegin(GL_QUAD_STRIP);

		for (j = 0; j <= 360; ++j)
		{
			angle = (float)PI * (float)j * (float)PI / 180.0f;
			x = radius * cos(angle) + bend_radius;
			y = radius * sin(angle);

			xb = sin(ang0) * x;
			yb = y;
			zb = cos(ang0) * x;
			glNormal3f(xb, yb, zb);
			glVertex3f(xb, yb, zb);

			xb = sin(ang1) * x;
			yb = y;
			zb = cos(ang1) * x;
			glNormal3f(xb, yb, zb);
			glVertex3f(xb, yb, zb);
		}
		glEnd();
	}
	glPopMatrix();
}

void Turntable::HandleKey(unsigned char key, int state, int mx, int my)
{
	// Ignore key-release
	if (!state) return;
	// Handle key
	switch (key)
	{
		// Press 'x' key to turn Animation on/off
	case 'x':
		ToggleAnimation();
		break;
		// Press 'z' key to toggle wire frame model

	}
}