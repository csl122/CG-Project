#include "Camera.h"
#include "VectorMath.h"
#include "Scene.h"
#include "Soldier.h"


Camera::Camera() : wKey(0), sKey(0), aKey(0), dKey(0), uKey(0), bKey(0), lKey(0), rKey(0), speed(8.f), sensitivity(1.f), control(0), currentButton(0), mouseX(0), mouseY(0)
{
	Reset();
}

void Camera::Reset(){
	// set the camera position to start at (0,0,0)
	eyePosition[0] = 0.0f;
	eyePosition[1] = 1350.0f; //1350 50
	eyePosition[2] = 300.f;//0.8f * static_cast<float>(Scene::GetWindowHeight()) / static_cast<float>(tan(M_PI / 6.0));//0.0f;

	// set the view direction vector of the camera to be (0,0,-1)
	vd[0] = 0.0f;
	vd[1] = 0.0f;
	vd[2] = 1.0f;

	// set the planar forward direction vector of the camera to be (0,0,-1)
	forward[0] = 0.0f;
	forward[1] = 0.0f;
	forward[2] = 1.0f;

	// set the right vector to point along the x axis
	right[0] = 1.0f;
	right[1] = 0.0f;
	right[2] = 0.0f;

	// set the up vector of the camera to be up the y axis
	up[0] = 0.0f;
	up[1] = 1.0f;
	up[2] = 0.0f;
}

void Camera::SetCameraPosition(float x, float y, float z)
{
	// set the camera position to start at (0,0,0)
	eyePosition[0] = x;
	eyePosition[1] = y;
	eyePosition[2] = z;//0.0f;

	// set the view direction vector of the camera to be (0,0,-1)
	vd[0] = 0.0f;
	vd[1] = 0.0f;
	vd[2] = -1.0f;

	// set the planar forward direction vector of the camera to be (0,0,-1)
	forward[0] = 0.0f;
	forward[1] = 0.0f;
	forward[2] = -1.0f;

	// set the right vector to point along the x axis
	right[0] = 1.0f;
	right[1] = 0.0f;
	right[2] = 0.0f;

	// set the up vector of the camera to be up the y axis
	up[0] = 0.0f;
	up[1] = 1.0f;
	up[2] = 0.0f;
}

void Camera::SetViewport()
{
	glViewport(static_cast<GLint>(0), static_cast<GLint>(0), static_cast<GLsizei>(Scene::GetWindowWidth()), static_cast<GLsizei>(Scene::GetWindowHeight()));
}

void Camera::SetupCamera()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyePosition[0], eyePosition[1], eyePosition[2],
			  eyePosition[0] + vd[0], eyePosition[1] + vd[1], eyePosition[2] + vd[2],
			  up[0], up[1], up[2]);

}

void Camera::Update(const double& deltaTime)
{
	bool _flagLose = Soldier::_flagLose;
	sensitivity = 0.0016f;
	ISoundEngine* musicEngine = Scene::GetMusicEngine();

	if (!_flagLose)
	{

		animateTime = 0;
		if ((aKey || dKey || wKey || sKey) && musicflat && !uKey && !bKey && (abs(eyePosition[1] - (50)) < 20 || abs(eyePosition[1] - (1350)) < 20)) {
			irrklang::ISound* runSound = musicEngine->play2D("./Media/run.mp3", true);
			if (runSound)
				runSound->setVolume(0.02f);
			musicflat = 0;
		}

		if (!aKey && !dKey && !wKey && !sKey && !musicflat || uKey || bKey) {
			musicEngine->removeSoundSource("./Media/run.mp3");
			musicflat = 1;
		}

		if (eyePosition[0] <= 1000.0f && eyePosition[0] >= -1000.0f && eyePosition[2] <= 1000.0f && eyePosition[2] >= -1000.0f) {

			if (aKey)
				sub(eyePosition, right, speed);


			if (dKey)
				add(eyePosition, right, speed);

			if (wKey)
				add(eyePosition, forward, speed);


			if (sKey)
				sub(eyePosition, forward, speed);
		}

		float lrlimit = 1000.f;
		float uplimit = 550.f;
		float btlimit = 50.f;
		float fblimit = 1000.f;
		float ublimit = 1000.f;

		if (eyePosition[1] >= 50.0f && eyePosition[1] <= 600.0f)
		{
			lrlimit = 1000.f;
			uplimit = 550.f;
			btlimit = 50.f;
			fblimit = 1000.f;
			ublimit = 1000.f;
		}
		else if (eyePosition[1] >= 1300.0f)
		{
			lrlimit = 110.f;
			uplimit = 1350.f;
			btlimit = 1350.f;
			fblimit = 570.f;
			ublimit = 470.f;
		}

		if (eyePosition[0] > lrlimit)
			eyePosition[0] = lrlimit;

		if (eyePosition[0] < -lrlimit)
			eyePosition[0] = -lrlimit;

		if (eyePosition[2] > ublimit)
			eyePosition[2] = ublimit;

		if (eyePosition[2] < -fblimit)
			eyePosition[2] = -fblimit;

		if (eyePosition[1] > uplimit)
			eyePosition[1] = uplimit;


		if (uKey)
			if (eyePosition[1] <= uplimit)
				add(eyePosition, up, speed);

		if (bKey)
			if (eyePosition[1] >= btlimit)
				sub(eyePosition, up, speed);

		sensitivity = 0.1f;

		//if (lKey) {
		//	sub(vd, right, sensitivity);
		//	// normalise the view direction so it is length 1
		//	norm(vd);

		//	// use the view direction crossed with the up vector to obtain the corrected right vector
		//	cross(vd, up, right);

		//	// normalise the right vector
		//	norm(right);

		//	/* As we want out camera to stay on the same plane at the same height (i.e. not move up and down the y axis) update a forward direction vector which can be used to move the camera. This forward vector moves the camera in the same direction as the view direction except it will not contain any y component so it cannot move off of its original height. This was we are free to look up and down however moving forward and back will not move us off of the camera plane. */

		//	forward[0] = vd[0];
		//	forward[2] = vd[2];
		//	norm(forward);
		//}
		//	
		//	

		//if (rKey) {
		//	add(vd, right, sensitivity);
		//	// normalise the view direction so it is length 1
		//	norm(vd);

		//	// use the view direction crossed with the up vector to obtain the corrected right vector
		//	cross(vd, up, right);

		//	// normalise the right vector
		//	norm(right);

		//	/* As we want out camera to stay on the same plane at the same height (i.e. not move up and down the y axis) update a forward direction vector which can be used to move the camera. This forward vector moves the camera in the same direction as the view direction except it will not contain any y component so it cannot move off of its original height. This was we are free to look up and down however moving forward and back will not move us off of the camera plane. */

		//	forward[0] = vd[0];
		//	forward[2] = vd[2];
		//	norm(forward);
		//}
	}
	else
	{
	animateTime += static_cast<float>(deltaTime);
	if (animateTime < 1.f)
	{
		up[0] = 1.0f * animateTime / 1.0f;
		up[1] = 1.0f - 1.0f * animateTime / 1.0f;
		up[2] = 0.0f;
	}
	
	}

		
	
	SetupCamera();
}

void Camera::GetEyePosition(float &x, float &y, float &z) const
{
	x = eyePosition[0];
	y = eyePosition[1];
	z = eyePosition[2];
}

void Camera::GetViewDirection(float &x, float &y, float &z) const
{
	x = vd[0];
	y = vd[1];
	z = vd[2];
}

void Camera::GetForwardVector(float &x, float &y, float &z) const
{
	x = forward[0];
	y = forward[1];
	z = forward[2];
}

void Camera::GetRightVector(float &x, float &y, float &z) const
{
	x = right[0];
	y = right[1];
	z = right[2];
}

void Camera::GetUpVector(float &x, float &y, float &z) const
{
	x = up[0];
	y = up[1];
	z = up[2];
}

void Camera::HandleKey(unsigned char key, int state, int x, int y)
{
	switch (key)
	{
		case 'A':
		case 'a':
			aKey = state;
			break;
		case 'D':
		case 'd':
			dKey = state;
			break;
		case 'W':
		case 'w':
			wKey = state;
			break;
		case 'S':
		case 's':
			sKey = state;
			break;
		case 'B':
		case 'b':
			Reset();
			break;
		case ' ':
			uKey = state;
			break;
		default:
			break;
	}
	printf_s("(%.0f, %.0f, %.0f)\n", eyePosition[0], eyePosition[1], eyePosition[2]);
}

void Camera::HandleSpecialKey(int key, int state, int x, int y)
{
	int mod = glutGetModifiers();

	if (mod == GLUT_ACTIVE_SHIFT)
		bKey = state;
	else if (mod == GLUT_ACTIVE_CTRL) {
		control = !control;
		if (control)
			speed = 2.f * speed;
		else
			speed = speed / 2.f;
	}
	else
		bKey = 0;
		//control = 0;

	/*switch (key)
	{
	case GLUT_KEY_UP:
		uKey = state;
		break;
	case GLUT_KEY_DOWN:
		bKey = state;
		break;
	case GLUT_KEY_LEFT:
		lKey = state;
		break;
	case GLUT_KEY_RIGHT:
		rKey = state;
		break;

	default:
		break;
	}*/
}

void Camera::HandleMouse(int button, int state, int x, int y)
{
	currentButton = button;
	mouseX = x;
	mouseY = y;
}

void Camera::HandleMouseDrag(int x, int y)
{
	bool _flagLose = Soldier::_flagLose;
	float rx, ry;
	float sensitivity = 0.01f; // speed of the camera moving

	if (!_flagLose)
	{


		// work out the difference between where the mouse was last used (mouseX, mouseY) to
		// position the view direction and the current position (x, y) the mouse is in
		rx = static_cast<float>(x - mouseX);
		ry = static_cast<float>(y - mouseY);

		// switch on which button was pressed and only do the update if the left button was pressed
		switch (currentButton)
		{
		case GLUT_RIGHT_BUTTON:

			// add on the amount of change in to the left and right view direction of the camera
			if (rx > 0)
				add(vd, right, rx * sensitivity);
			else
				sub(vd, right, rx * -sensitivity);
			// add on the amount of change in to the up and down view direction of the camera
			if (ry > 0)
				sub(vd, up, ry * sensitivity);
			else
				add(vd, up, ry * -sensitivity);

			// normalise the view direction so it is length 1
			norm(vd);

			// use the view direction crossed with the up vector to obtain the corrected right vector
			cross(vd, up, right);

			// normalise the right vector
			norm(right);

			/* As we want out camera to stay on the same plane at the same height (i.e. not move up and down the y axis) update a forward direction vector which can be used to move the camera. This forward vector moves the camera in the same direction as the view direction except it will not contain any y component so it cannot move off of its original height. This was we are free to look up and down however moving forward and back will not move us off of the camera plane. */

			forward[0] = vd[0];
			forward[2] = vd[2];
			norm(forward);
			break;
		case GLUT_LEFT_BUTTON:
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		default:
			break;
		}

		mouseX = x;
		mouseY = y;
	}
}