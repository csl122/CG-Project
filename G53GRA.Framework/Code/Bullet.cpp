#include "Bullet.h"
#include "Soldier.h"
#define PI acos(-1)

bool Bullet::_flagLose = false;

Bullet::Bullet(MyScene* scene, Vertex* color, int winding) : WorldObject(scene, 0, "test", 0),
scene(scene), _flagAutospin(false), ifWin(false),
_flagReset(false), _iKey(false), _jKey(false), _kKey(false),
_lKey(false), _oKey(false), _uKey(false), _plusKey(false), _minusKey(false),
_upKey(false), _downKey(false), _leftKey(false), _rightKey(false), currentx(0), currentz(0)
{

	_obj_path = "./Obj/bullet.obj";
	_tex_path = "./Textures/sky.bmp";
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


Bullet::~Bullet()
{
}

void Bullet::SetLose(bool flag)
{
	_flagLose = flag;
}


void Bullet::Display() {
	glDisable(GL_CULL_FACE);
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);

	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f); // angle ry about (0,1,0)
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f); // angle rz about (0,0,1)
	glRotatef(rotation[0], 1.0f, 0.0f, 0.0f); // angle rx about (1,0,0)

	glTranslatef(currentx, currentz, 0);

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

void Bullet::Render() {

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

void Bullet::RenderFace(Face* face) {

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

void Bullet::RenderVertex(int vertexIndex) {
	Vertex* vertexCoordinates = vertices[vertexIndex];
	glVertex3f(vertexCoordinates->x, vertexCoordinates->y, vertexCoordinates->z);
}

void Bullet::RenderNormal(int normalIndex) {
	auto normal = normals[normalIndex];
	glNormal3f(normal->x, normal->y, normal->z);
}

void Bullet::RenderMaterial(int materialIndex) {
	float* materialCoordinate = textureCoordinates[materialIndex];
	float one = materialCoordinate[0];
	float two = materialCoordinate[1];
	glTexCoord2f(materialCoordinate[0], materialCoordinate[1]);
}

void Bullet::setScale(Vertex* size) {
	this->vSize = size;
	scale[0] = vSize->x;
	scale[1] = vSize->y;
	scale[2] = vSize->z;
}

void Bullet::setPosition(Vertex* position) {
	this->vPosition = position;
	pos[0] = vPosition->x;
	pos[1] = vPosition->y;
	pos[2] = vPosition->z;

}

void Bullet::setOrientation(Vertex* orientation) {
	this->vOrientation = orientation;
	rotation[0] = vOrientation->x;
	rotation[1] = vOrientation->y;
	rotation[2] = vOrientation->z;
}

void Bullet::Update(const double& deltaTime) {

	// get player's position for aiming
	float x, y, z;
	Camera* camera = Scene::GetCamera();
	camera->GetEyePosition(x, y, z);

	// calculating facing direction
	float x1 = vPosition->x;
	float z1 = -vPosition->z;
	float x2 = x - vPosition->x;
	float z2 = z - vPosition->z;
	float cosine = float((x1 * x2 + z1 * z2) / (sqrt(x1 * x1 + z1 * z1) * sqrt(x2 * x2 + z2 * z2)));
	float angle;
	if (x > 0)
	{
		angle = float(acos(cosine) / (2 * PI) * 360);
	}
	else
	{
		angle = float(acos(cosine) / (2 * PI) * 360 * -1);
	}
	rotation[1] = 180 + angle;

	// shoot the bullet when lose the game
	if (Soldier::_flagLose && animateRotation < 1)
	{

		animateTime += static_cast<float>(deltaTime);
		animateRotation += static_cast<float>(deltaTime);

		pos[0] = vPosition->x + x2 * ((z2 + 500) / z2) * animateRotation/1;
		pos[2] = vPosition->z + (z2+500) *  animateRotation/1;
		currentx = -0.8f;
		currentz = -0.4f;

	}
	else
	{
		position(vPosition->x, vPosition->y, vPosition->z);
		currentx = 0.f;
		currentz = 0.f;
	}

	// reset status of bullet
	if (_flagReset)
	{
		size(vSize->x, vSize->y, vSize->z);
		position(vPosition->x, vPosition->y, vPosition->z);
		orientation(vOrientation->x, vOrientation->y, vOrientation->z);
		animateRotation = 0;
		animateTime = 0;
		currentx = 0.f;
		currentz = 0.f;
		_flagReset = false;
	}
}




void Bullet::HandleKey(unsigned char key, int state, int x, int y)
{
	switch (key)
	{
	
	case 'b':
	case 'B':
		_flagReset = true;
		break;
	}
}

void Bullet::HandleSpecialKey(int key, int state, int x, int y)
{

}