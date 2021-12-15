//#include "Timer.h"
//#include <iostream>
//#include "Soldier.h"
//#include "Head.h"
//using namespace std;
//
///// initalise the Timers properties
//Timer::Timer() : xrot(0.0f), yrot(0.0f), zrot(0.0f), scale(0.5f), _flagReset(false), animateTime(0.f), animateRotation(0.f), keyframe(-1), interpTime(0),  _obj_path("./Textures/timer20.bmp") { _tex_path = "./Textures/timer20.bmp"; }
//
///// draw the Timer in the scene
//void Timer::Display()
//{
//	
//	glPushMatrix();
//	glBegin(GL_QUADS);
//
//	glColor3ub(255, 255, 255);
//	glEnable(GL_TEXTURE_2D);
//
//	// prompt board
//	glBindTexture(GL_TEXTURE_2D, Scene::GetTexture(_tex_path));
//	glBegin(GL_QUADS);
//	glNormal3f(0.0f, 0.0f, 1.0f);
//	glTexCoord2f(0.0f, 1.0f);
//	glVertex3f(220.f, 1400.f, 600.0f);
//	glTexCoord2f(0.0f, 0.0f);
//	glVertex3f(220.f, 1250.f, 600.0f);
//	glTexCoord2f(1.0f, 0.0f);
//	glVertex3f(20.f, 1250.f, 600.0f);
//	glTexCoord2f(1.0f, 1.0f);
//	glVertex3f(20.f, 1400.f, 600.0f);
//	glEnd();
//	glDisable(GL_TEXTURE_2D);
//
//
//	glEnd();
//	glPopMatrix();
//}
//
///// update the Z rotation variable with change in time
//void Timer::Update(const double& deltaTime)
//{
//	bool _flagLose = Soldier::_flagLose;
//	bool _flagStart = Head::_flagStart;
//	ISoundEngine* musicEngine = Scene::GetMusicEngine();
//
//	if (!_flagLose && _flagStart)
//	{
//
//
//		animateTime += static_cast<float>(deltaTime);
//		animateRotation += static_cast<float>(deltaTime);
//
//		// check if we hit the end of the animation (3 seconds), if so reset
//		if (animateTime >= 8.0f)
//		{
//			animateTime = 0.0f;
//			keyframe = -1;
//		}
//
//		// check if we are in the 1st second of animation
//		if (animateTime < 0.5f)
//		{
//
//			// check if we have only just entered the 1st keyframe in which case
//			// set up the parameters
//			if (keyframe != 0)
//			{
//				animateTime = 0.0f;
//				animateRotation = 0.0f;
//				keyframe = 0;
//				interpTime = 0.5f;
//				_tex_path = "./Textures/head.bmp";
//			}
//		}
//		// check if we are in the 1.0 to 1.25 seconds of animation
//		else if (animateTime < 5.f)
//		{
//			// check if we have only just entered the 2nd keyframe in which case 
//			// set up the parameters
//			if (keyframe != 1)
//			{
//				keyframe = 1;
//				animateRotation = 0.0f;
//				interpTime = 4.f;
//			}
//
//		}
//		else if (animateTime < 5.7f)
//		{
//			// check if we have only just entered the 2nd keyframe in which case 
//			// set up the parameters
//			if (keyframe != 2)
//			{
//				keyframe = 2;
//				animateRotation = 0.0f;
//				interpTime = 0.7f;
//			}
//		}
//		else
//		{
//
//			if (keyframe != 3)
//			{
//				keyframe = 3;
//				animateRotation = 0.0f;
//				interpTime = 2.3f;
//				_tex_path = "./Textures/headred.bmp";
//
//
//			}
//			
//		}
//	}
//
//	if (_flagReset)
//	{
//		animateRotation = 0;
//		animateTime = 0;
//		_flagReset = false;
//	}
//	
//}
//
///// set scale variables based on a key press
//void Timer::HandleKey(unsigned char key, int state, int x, int y)
//{
//	switch (key)
//	{
//
//	case 'b':
//	case 'B':
//		_flagReset = true;
//		break;
//	case 'f':
//		break;
//		//if (state == 0) {
//			//_flagAutospin = !_flagAutospin;
//			//break;
//		//}
//	}
//}
