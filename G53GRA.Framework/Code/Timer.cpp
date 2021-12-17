#include "Timer.h"
#include "Head.h"
#include "Soldier.h"

bool Timer::_flagStart = false;

Timer::Timer(MyScene* scene, string fileName, Vertex* color, int winding) : WorldObject(scene, 0, "test", 0),
scene(scene), _flagAutospin(false), ifWin(false), keyframe(-1), animateTime(0.0), animateRotation(0.0), interpA(0.0), interpB(0.0), interpTime(0.0),
_flagReset(false), _iKey(false), _jKey(false), _kKey(false),
_lKey(false), _oKey(false), _uKey(false), _plusKey(false), _minusKey(false),
_upKey(false), _downKey(false), _leftKey(false), _rightKey(false), _flagMove(false), _flagLose(false)
{
	_filename = fileName;
	_tex_path = "./Textures/2.bmp";
	defaultColor = color;


	//glFrontFace(winding);

	static GLfloat mat_ambient[] = { 1.f, 1.f, 1.f, 1.f };
	// Define the diffuse material colour property K_d
	static GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.f };
	// Define the specular material colour property K_s
	static GLfloat mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.f };
	// Define the shininess/specular exponent factor n ( capped between 0.0 and 128.0 )
	static GLfloat mat_shininess[] = { 30.0f };

	_mat_ambient = mat_ambient;
	_mat_diffuse = mat_diffuse;
	_mat_specular = mat_specular;
	_mat_shininess = mat_shininess;

	size(_INIT_SIZE);
	pos[2] = _DEF_Z * 2;


	//_texID2 = scene->GetTexture(_tex_path2);
}


Timer::~Timer()
{
}

void Timer::Display() {
	
	glDisable(GL_COLOR_MATERIAL);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, _mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, _mat_diffuse);
	
	glPushMatrix();
	

	glColor3ub(0, 0, 0);
	
	glEnable(GL_TEXTURE_2D);

	// prompt board
	glBindTexture(GL_TEXTURE_2D, Scene::GetTexture(_tex_path));
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-100, 542, -1099);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-100, 458, -1099);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(100, 458, -1099);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(100, 542, -1099);
	glEnd();
	
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	
}

void Timer::Render() {
	//glEnable(GL_TEXTURE_2D);
	//glEnable(GL_COLOR_MATERIAL);

	//glBindTexture(GL_TEXTURE_2D, textureId);
	//float light_position[] = { 0.0f, 1.0f, 0.0f, 0.0f };
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//glColor3f(defaultColor->x, defaultColor->y, defaultColor->z);

	//auto alreadyRenderedFaces = false;
	//auto currentTextureId = Materials::NONE;


	for (size_t faceId = 0; faceId < faces.size(); faceId++) {
		//auto faceMaterial = faceMaterials[faceId];
		//auto textureChanged = faceMaterial != currentTexture;

		Face* face = faces[faceId];
		glColor3f(1.f, 1.f, 1.f);
		if (face->faceData->size() == 3) {
			glBegin(GL_TRIANGLES);
		}
		else {
			glBegin(GL_QUADS);
		}
		RenderFace(face);
		glEnd();
	}

}

void Timer::RenderFace(Face* face) {

	vector<Vertex*>* faceData = face->faceData;

	for (size_t vertexId = 0; vertexId < faceData->size(); ++vertexId) {
		Vertex* data = faceData->at(vertexId);

		int normalIndex = (int)data->z; // Index position of the normal within the normals list
		if (normalIndex > -1 && normalIndex < (int)normals.size())
			RenderNormal(normalIndex);

		int materialIndex = (int)data->y; // Index position of the material within the materials list
		if (materialIndex > -1 && materialIndex < (int)textureCoordinates.size())
			RenderMaterial(materialIndex);

		int vertexIndex = (int)data->x; // Index position of the vertex within the vertices list
		if (vertexIndex > -1 && vertexIndex < (int)vertices.size())
			RenderVertex(vertexIndex);

	}
}

void Timer::RenderVertex(int vertexIndex) {
	Vertex* vertexCoordinates = vertices[vertexIndex];
	glVertex3f(vertexCoordinates->x, vertexCoordinates->y, vertexCoordinates->z);
}

void Timer::RenderNormal(int normalIndex) {
	auto normal = normals[normalIndex];
	glNormal3f(normal->x, normal->y, normal->z);
	//glColor3f(normal->x, normal->y, normal->z);
}

void Timer::RenderMaterial(int materialIndex) {
	float* materialCoordinate = textureCoordinates[materialIndex];
	float one = materialCoordinate[0];
	float two = materialCoordinate[1];
	glTexCoord2f(materialCoordinate[0], materialCoordinate[1]);
}

void Timer::setScale(Vertex* size) {
	this->vSize = size;
	scale[0] = vSize->x;
	scale[1] = vSize->y;
	scale[2] = vSize->z;
}

void Timer::setPosition(Vertex* position) {
	this->vPosition = position;
	//position(vPosition->x, vPosition->y, vPosition->z);
	pos[0] = vPosition->x;
	pos[1] = vPosition->y;
	pos[2] = vPosition->z;

}

void Timer::setOrientation(Vertex* orientation) {
	this->vOrientation = orientation;
	rotation[0] = vOrientation->x;
	rotation[1] = vOrientation->y;
	rotation[2] = vOrientation->z;
}


void Timer::Update(const double& deltaTime) {
	float velocity = 100.0f * static_cast<float>(deltaTime);
	float shrinkRate = -5.0f * static_cast<float>(deltaTime);
	ISoundEngine* musicEngine = Scene::GetMusicEngine();
	float x, y, z;
	Camera* camera = Scene::GetCamera();
	camera->GetEyePosition(x, y, z);
	_flagLose = Soldier::_flagLose;
	_flagStart = Head::_flagStart;
	ifWin = Head::ifWin;




	if (!ifWin && !_flagLose && _flagStart)
	{

		
		animateTime += static_cast<float>(deltaTime);
		animateRotation += static_cast<float>(deltaTime);
		
		// check if we hit the end of the animation (3 seconds), if so reset
		if (animateTime >= 21.0f)
		{
			animateTime = 0.0f;
			keyframe = -1;
		}
		
		int count = 20 - int(floor(animateTime));
		string num = to_string(count);
		//printf("%f, %d\n", animateTime, count);
		_tex_path = "./Textures/" + num + ".bmp";


		if (count == 0)
		{
			animateTime = 0.0f;
			Soldier::SetLose(true);
			musicEngine->removeAllSoundSources();
			musicEngine->play2D("./Media/lose.mp3", false);
			musicEngine->play2D("./Media/gun.mp3", false);
		}

		
			
		
	}






	// Spacebar will reset transformation values
	if (_flagReset)
	{
		_flagReset = false;
		animateTime = 0.0f;
	}




}


void Timer::HandleKey(unsigned char key, int state, int x, int y)
{
	/*
	This function is called continuously when a key is pressed AND when
	it is released. The variable 'key' describes the character or the key,
	e.g. for the a key, key == 'a'. Variable 'state' describes whether the
	key has been pressed or released. While the key is pressed, state = 1,
	when released, the function is called with state = 0. x and y describe
	position of the mouse at callback (this can be ignored for now).
	*/

	// Switch on key char
	// Set flag for control keys, (i,j,k,l,o,u,+,-,space) to state value
	// i.e. if 'i' is pressed, _iKey = true, if 'i' released, _iKey = false
	switch (key)
	{
	
	case 'b':
	case 'B':
		_flagReset = true;
		break;
	
	}
}

void Timer::HandleSpecialKey(int key, int state, int x, int y)
{

}




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
