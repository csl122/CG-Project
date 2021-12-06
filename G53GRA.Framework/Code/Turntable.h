#pragma once

#include "DisplayableObject.h"
#include "Animation.h"

/*
This is a class that should dispaly our lamp with they rough rigid body
transform between our key frames
Here is a more complex example of the effects that can be achieved:
http://www.youtube.com/watch?v=cdtHSyfcSDs
*/

class Turntable :
	public DisplayableObject,
	public Animation,
	public Input
{
public:
	Turntable();
	~Turntable() {};

	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int mx, int my);
	inline void ToggleAnimation() { _flagAnimation = !_flagAnimation; }

private:

	void DrawCube();            // function to draw a unit cube over the origin
	void snowMan();
	void snowHand();
	void DrawSnowMan();
	void Circle(float r);
	void drawCylinder(GLdouble r, GLdouble h);
	void drawHorse();
	void drawTurntable();
	void CurvedCylinder(GLfloat radius, GLfloat height);

	GLboolean _flagAnimation;
	int keyframe;               // variable to track which keyframe we are on
	float animateTime;          // variable to store the current time the animation has run for
	float animateRotation;      // variable to track the current amount of rotation steps
	float animateTranslation;   // variable to track the current amount of translation steps
	float interpA;              // variable to hold what the first keyframe angle is
	float interpB;              // variable to hold what the second keyframe angle is
	float sizeA;
	float sizeB;
	float interpTime;           // variable to track how long the keyframe lasts i.e. how long do we have
								// to move from interpA to interpB

};

#pragma once
