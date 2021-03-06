#include "Head.h"
#include "Soldier.h"

// global bool for the game status
bool Head::_flagStart = false;
bool Head::ifWin = false;

Head::Head(MyScene* scene, string fileName, Vertex* color, int winding) : WorldObject(scene, 0, "test", 0),
scene(scene), _flagAutospin(false), keyframe(-1), animateTime(0.0), animateRotation(0.0), interpA(0.0), interpB(0.0), interpTime(0.0),
_flagReset(false), _iKey(false), _jKey(false), _kKey(false),
_lKey(false), _oKey(false), _uKey(false), _plusKey(false), _minusKey(false),
_upKey(false), _downKey(false), _leftKey(false), _rightKey(false), _flagMove(false), _flagLose(false)
{
	_filename = fileName;
	_obj_path = "./Obj/" + _filename + ".obj";
	_tex_path = "./Textures/" + _filename + ".bmp";
	defaultColor = color;

	objectFileReader = new ObjectFileReader(_obj_path);
	objectFileReader->Load();

	vertices = objectFileReader->vertices;
	normals = objectFileReader->normals;
	textureCoordinates = objectFileReader->textureCoordinates;
	faces = objectFileReader->faces;
	faceMaterials = objectFileReader->faceMaterials;

	_texID = scene->GetTexture(_tex_path);


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
}


Head::~Head()
{
}

void Head::Display() {
	glDisable(GL_CULL_FACE);
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);

	//rotation[0] = -90.0f;

	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f); // angle ry about (0,1,0)
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f); // angle rz about (0,0,1)
	glRotatef(rotation[0], 1.0f, 0.0f, 0.0f); // angle rx about (1,0,0)

	glRotatef(interpA + animateRotation * ((interpB - interpA) / interpTime), 0.0f, 1.0f, 0.0f);

	glMaterialfv(GL_FRONT, GL_AMBIENT, _mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _mat_diffuse);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _texID);
	glColor3f(1, 1, 1);
	glutSolidSphere(1, 1, 1);
	Render();

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glEnable(GL_CULL_FACE);
}

void Head::Render() {

	for (size_t faceId = 0; faceId < faces.size(); faceId++) {

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

void Head::RenderFace(Face* face) {

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

void Head::RenderVertex(int vertexIndex) {
	Vertex* vertexCoordinates = vertices[vertexIndex];
	glVertex3f(vertexCoordinates->x, vertexCoordinates->y, vertexCoordinates->z);
}

void Head::RenderNormal(int normalIndex) {
	auto normal = normals[normalIndex];
	glNormal3f(normal->x, normal->y, normal->z);
}

void Head::RenderMaterial(int materialIndex) {
	float* materialCoordinate = textureCoordinates[materialIndex];
	float one = materialCoordinate[0];
	float two = materialCoordinate[1];
	glTexCoord2f(materialCoordinate[0], materialCoordinate[1]);
}

void Head::setScale(Vertex* size) {
	this->vSize = size;
	scale[0] = vSize->x;
	scale[1] = vSize->y;
	scale[2] = vSize->z;
}

void Head::setPosition(Vertex* position) {
	this->vPosition = position;
	pos[0] = vPosition->x;
	pos[1] = vPosition->y;
	pos[2] = vPosition->z;

}

void Head::setOrientation(Vertex* orientation) {
	this->vOrientation = orientation;
	rotation[0] = vOrientation->x;
	rotation[1] = vOrientation->y;
	rotation[2] = vOrientation->z;
}


void Head::Update(const double& deltaTime) {
	float velocity = 100.0f * static_cast<float>(deltaTime);
	float shrinkRate = -5.0f * static_cast<float>(deltaTime);
	ISoundEngine* musicEngine = Scene::GetMusicEngine();
	float x, y, z;
	Camera* camera = Scene::GetCamera();
	camera->GetEyePosition(x, y, z);
	_flagLose = Soldier::_flagLose;
	

	if (!ifWin && !_flagLose && _flagStart)
	{


		animateTime += static_cast<float>(deltaTime);
		animateRotation += static_cast<float>(deltaTime);

		// turn head every 8 seconds
		if (animateTime >= 8.0f)
		{
			animateTime = 0.0f;
			keyframe = -1;
		}

		if (animateTime < 0.5f)
		{
			
			// initial status
			if (keyframe != 0)
			{
				animateTime = 0.0f;
				animateRotation = 0.0f;
				keyframe = 0;
				interpA = 0.0f;
				interpB = 180.0f;
				interpTime = 0.5f;
				_tex_path = "./Textures/head.bmp";
				_texID = scene->GetTexture(_tex_path);
				glEnable(GL_LIGHT0);
				glDisable(GL_LIGHT3);
			}
		}
		// not move
		else if (animateTime < 5.f)
		{
			if (keyframe != 1)
			{
				keyframe = 1;
				animateRotation = 0.0f;
				interpA = 180.0f;
				interpB = 180.0f;
				interpTime = 4.f;
			}
			
		}
		// turning head
		else if (animateTime < 5.7f)
		{
			if (keyframe != 2)
			{
				keyframe = 2;
				animateRotation = 0.0f;
				interpA = 180.0f;
				interpB = 0.0f;
				interpTime = 0.7f;
			}
		}
		else
		{
			// facing to the user
			if (keyframe != 3)
			{
				keyframe = 3;
				animateRotation = 0.0f;
				interpA = 0.0f;
				interpB = 0.0f;
				interpTime = 2.3f;
				_tex_path = "./Textures/headred.bmp";
				_texID = scene->GetTexture(_tex_path);
				
				glDisable(GL_LIGHT0);
				glEnable(GL_LIGHT3);
				
			}

			// lose if motion is detected
			if (_flagMove && abs(y - (50)) < 20)
			{
				_flagLose = true;
				animateRotation = 0;
				Soldier::SetLose(true);
				musicEngine->removeAllSoundSources();
				musicEngine->play2D("./Media/lose.mp3", false);
				musicEngine->play2D("./Media/gun.mp3", false);

				
			}

			//scanning light
			GLfloat spot3_direction[] = { 0.0,-1 - -1.0 *(animateRotation/interpTime),1.0 };
			glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot3_direction);
		}
	}
	
	// set lose lighting
	if (_flagLose)
	{
		float scale = 1.f;
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT0); 
		
		animateRotation += static_cast<float>(deltaTime);
		if (animateRotation < 3)
		{
			//directional 4
			scale = 1- scale * (animateRotation / 3);
			GLfloat ambience4[] = { 0.2f* scale, 0.2f * scale, 0.2f * scale, 1.0f };
			GLfloat diffuse4[] = { 0.5f * scale, 0.5f * scale, 0.5f * scale, 1.0f };
			GLfloat specular4[] = { 1.0f * scale, 1.0f * scale, 1.0f * scale, 1.0f };
			GLfloat position4[] = { 0.0f, 1.0f, 0.2f, 0.0f };
			glLightfv(GL_LIGHT4, GL_AMBIENT, ambience4);
			glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse4);
			glLightfv(GL_LIGHT4, GL_SPECULAR, specular4);
			glLightfv(GL_LIGHT4, GL_POSITION, position4);
			glEnable(GL_LIGHT4);

			// global
			GLfloat global_ambient[] = { 0.05+0.2f * scale ,  0.05 + 0.2f * scale,  0.05 + 0.2f * scale };
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

			// spotlight 5
			scale = 1 - scale;
			GLfloat ambience5[] = { 0.2f * scale, 0.0f * scale, 0.0f * scale, 1.0f };
			GLfloat diffuse5[] = { 0.8f * scale, 0.0f * scale, 0.0f * scale, 1.0f };
			GLfloat specular5[] = { 1.0f * scale, 0.0f * scale, 0.0f * scale, 1.0f };
			GLfloat position5[] = { 0.0, 450.0, -1000.0,1.0 };
			GLfloat spot5_direction[] = { 0.0f, -1, 0.f };
			glLightfv(GL_LIGHT5, GL_AMBIENT, ambience5);
			glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuse5);
			glLightfv(GL_LIGHT5, GL_SPECULAR, specular5);
			glLightfv(GL_LIGHT5, GL_POSITION, position5);
			glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 30.0);//angle
			glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spot5_direction);//direction
			glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 10.5);
			glEnable(GL_LIGHT5);

		}
		else
		{
			// spotlight 5
			scale = 1;
			GLfloat ambience5[] = { 0.2f * scale, 0.0f * scale, 0.0f * scale, 1.0f };
			GLfloat diffuse5[] = { 0.8f * scale, 0.0f * scale, 0.0f * scale, 1.0f };
			GLfloat specular5[] = { 1.0f * scale, 0.0f * scale, 0.0f * scale, 1.0f };
			GLfloat position5[] = { 0.0, 450.0, -1000.0,1.0 };
			GLfloat spot5_direction[] = { 0.0f, -1, 0.f };
			glLightfv(GL_LIGHT5, GL_AMBIENT, ambience5);
			glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuse5);
			glLightfv(GL_LIGHT5, GL_SPECULAR, specular5);
			glLightfv(GL_LIGHT5, GL_POSITION, position5);
			glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 30.0);
			glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spot5_direction);
			glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 10.5);
			glEnable(GL_LIGHT5);
		}

	}
	
	
	// starting
	if (abs(x - 0) < 200 && abs(z - (-570)) < 10 && abs(y - (1350)) < 10)
	{
		//transmit user to the playground and start the game
		camera->SetCameraPosition(0.f, 50.f, 935.f); //(0.f ,50.f, 935.f)(0., 1350.0f, 500.)
		
		_flagStart = true;
		glEnable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		GLfloat global_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
		musicEngine->removeSoundSource("./Media/back1.wav");
		musicEngine->play2D("./Media/wood.mp3", true);
	}

	// winning
	if (!ifWin && z < -700 && abs(y - (50)) < 20 && !_flagLose)
	{
		ifWin = true;
		musicEngine->removeAllSoundSources();
		musicEngine->play2D("./Media/win.mp3", false);
	}

	// resetting
	if (_flagReset)
	{
		
		size(vSize->x, vSize->y, vSize->z);
		position(vPosition->x, vPosition->y, vPosition->z);
		orientation(vOrientation->x, vOrientation->y, vOrientation->z);
		_flagStart = false;
		_flagReset = false;
		_flagLose = false;
		ifWin = false;
		animateTime = 0.0f;
		keyframe = -1;
		musicEngine->removeAllSoundSources();
		musicEngine->play2D("./Media/back1.wav", true);
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT4);
		glDisable(GL_LIGHT5);
		GLfloat global_ambient[] = { 0.05f, 0.05f, 0.05f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
		Soldier::SetLose(false);
	}

	/*
	If keys pressed down:
	[u][i][o]
	[j][k][l]

	rotate around x,y,z axes for (i,k), (j,l) and (u,o) respectively
	*/

	if (_flagAutospin) {
		rotation[0] -= velocity;
		rotation[1] -= velocity;
	}

	// 'i' pressed down, decrease rotation around 'x'
	if (_iKey) rotation[0] -= velocity;
	// 'j' pressed down, decrease rotation around 'y'
	if (_jKey) rotation[1] -= velocity;
	// 'k' pressed down, increase rotation around 'x'
	if (_kKey) rotation[0] += velocity;
	// 'l' pressed down, increase rotation around 'y'
	if (_lKey) rotation[1] += velocity;
	// 'o' pressed down, decrease rotation around 'z'
	if (_oKey) rotation[2] -= velocity;
	// 'u' pressed down, increase rotation around 'x'
	if (_uKey) rotation[2] += velocity;

	/*
	If keys pressed down:
	[-]
	|+|  or   [-]^[+]
	|_|
	scale by all x,y,z axes equally, + to grow, - to shrink
	*/
	// '-' pressed down (and no scale value is below 1.0)
	if (_minusKey && scale[0] > 1.0f && scale[1] > 1.0f && scale[2] > 1.0f)
	{
		// increase shrinkage by constant (negative) rate
		scale[0] += shrinkRate;
		scale[1] += shrinkRate;
		scale[2] += shrinkRate;
	}
	// '+' pressed down
	if (_plusKey)
	{
		// decrease shrinkage (e.g. grow)
		scale[0] -= shrinkRate;
		scale[1] -= shrinkRate;
		scale[2] -= shrinkRate;
	}

	/*
	If keys pressed down:
	[/\]
	[<-][\/][->]
	translate along x and y axes, for (left, right) and (up, down) respectively
	*/
	float current = rotation[1];

	if (_upKey) {
		pos[2] -= velocity;

		if (rotation[1] > -180.0) rotation[1] -= 30;
		if (rotation[1] < -180.0) rotation[1] += 30;
	}
	if (_downKey) {
		pos[2] += velocity;
		if (rotation[1] > 0) rotation[1] -= 30;
		if (rotation[1] < 0) rotation[1] += 30;
	}

	if (_leftKey) {
		pos[0] -= velocity;
		if (rotation[1] > -90) rotation[1] -= 30;
		if (rotation[1] < -90) rotation[1] += 30;
	}
	if (_rightKey) {
		pos[0] += velocity;
		if (rotation[1] > 90) rotation[1] -= 30;
		if (rotation[1] < 90) rotation[1] += 30;
	}

	if (_pageDn) {
		pos[1] -= velocity;
	}
	if (_pageUp) {
		pos[1] += velocity;
	}
}


void Head::HandleKey(unsigned char key, int state, int x, int y)
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
	case 'i':
	case 'I':
		_iKey = static_cast<GLboolean>(state);
		break;
	case 'j':
	case 'J':
		_jKey = static_cast<GLboolean>(state);
		break;
	case 'k':
	case 'K':
		_kKey = static_cast<GLboolean>(state);
		break;
	case 'l':
	case 'L':
		_lKey = static_cast<GLboolean>(state);
		break;
	case 'o':
	case 'O':
		_oKey = static_cast<GLboolean>(state);
		break;
	case 'u':
	case 'U':
		_uKey = static_cast<GLboolean>(state);
		break;
	case '+': // with shift
	case '=': // without shift
		_plusKey = static_cast<GLboolean>(state);
		break;
	case '-':
		_minusKey = static_cast<GLboolean>(state);
		break;
	case 'b':
	case 'B':
		_flagReset = true;
		break;
	case 'f':
		break;
	case 'w':
	case 'a':
	case 's':
	case 'd':
	case 'W':
	case 'A':
	case 'S':
	case 'D':
		_flagMove = static_cast<GLboolean>(state);
		break;
	}
}

void Head::HandleSpecialKey(int key, int state, int x, int y)
{
	/*
	This function is called continuously when a special key is pressed
	AND when it is released. The variable 'key' describes the keycode
	for the key, e.g. for the UP key, key == 0x0065 (or GLUT_KEY_UP).
	Variable 'state' describes whether the key has been pressed or
	released. While the key is pressed, state = 1, when released, the
	function is called with state = 0. x and y describe position of the
	mouse at callback.
	See the Lab 4 for details on special keys.
	*/

	// Switch on key code (using GLUT #defines)
	// Set flag for control keys, (up, down, left, right) to state value
	// i.e. if 'up' is pressed, _upKey = true, if 'up' released, _upKey = false
	switch (key)
	{
	case GLUT_KEY_UP:
		_upKey = static_cast<GLboolean>(state);
		break;
	case GLUT_KEY_DOWN:
		_downKey = static_cast<GLboolean>(state);
		break;
	case GLUT_KEY_LEFT:
		_leftKey = static_cast<GLboolean>(state);
		break;
	case GLUT_KEY_RIGHT:
		_rightKey = static_cast<GLboolean>(state);
		break;
	case GLUT_KEY_PAGE_UP:
		_pageUp = static_cast<GLboolean>(state);
		break;
	case GLUT_KEY_PAGE_DOWN:
		_pageDn = static_cast<GLboolean>(state);
		break;
	}
}