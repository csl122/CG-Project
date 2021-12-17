#include "Soldier.h"

bool Soldier::_flagLose = false;

Soldier::Soldier(MyScene* scene, string fileName, string fileName2, Vertex* color, int winding) : WorldObject(scene, 0, "test", 0),
scene(scene), _flagAutospin(false), ifWin(false),
_flagReset(false), _iKey(false), _jKey(false), _kKey(false),
_lKey(false), _oKey(false), _uKey(false), _plusKey(false), _minusKey(false),
_upKey(false), _downKey(false), _leftKey(false), _rightKey(false)
{
	_filename = fileName;
	_filename2 = fileName2;
	_obj_path = "./Obj/" + _filename + ".obj";
	_tex_path = "./Textures/squid.bmp";
	//_tex_path2 = "Texture/" + fileName + "2.bmp";
	defaultColor = color;

	objectFileReader = new ObjectFileReader(_obj_path);
	objectFileReader->Load();

	vertices = objectFileReader->vertices;
	normals = objectFileReader->normals;
	textureCoordinates = objectFileReader->textureCoordinates;
	faces = objectFileReader->faces;
	faceMaterials = objectFileReader->faceMaterials;

	_texID = scene->GetTexture(_tex_path);

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
}


Soldier::~Soldier()
{
}

void Soldier::SetLose(bool flag)
{
	_flagLose = flag;
}


void Soldier::Display() {
	glDisable(GL_CULL_FACE);
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);


	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f); // angle ry about (0,1,0)
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f); // angle rz about (0,0,1)
	glRotatef(rotation[0], 1.0f, 0.0f, 0.0f); // angle rx about (1,0,0)

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

void Soldier::Render() {

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

void Soldier::RenderFace(Face* face) {

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

void Soldier::RenderVertex(int vertexIndex) {
	Vertex* vertexCoordinates = vertices[vertexIndex];
	glVertex3f(vertexCoordinates->x, vertexCoordinates->y, vertexCoordinates->z);
}

void Soldier::RenderNormal(int normalIndex) {
	auto normal = normals[normalIndex];
	glNormal3f(normal->x, normal->y, normal->z);
}

void Soldier::RenderMaterial(int materialIndex) {
	float* materialCoordinate = textureCoordinates[materialIndex];
	float one = materialCoordinate[0];
	float two = materialCoordinate[1];
	glTexCoord2f(materialCoordinate[0], materialCoordinate[1]);
}

void Soldier::setScale(Vertex* size) {
	this->vSize = size;
	scale[0] = vSize->x;
	scale[1] = vSize->y;
	scale[2] = vSize->z;
}

void Soldier::setPosition(Vertex* position) {
	this->vPosition = position;
	pos[0] = vPosition->x;
	pos[1] = vPosition->y;
	pos[2] = vPosition->z;

}

void Soldier::setOrientation(Vertex* orientation) {
	this->vOrientation = orientation;
	rotation[0] = vOrientation->x;
	rotation[1] = vOrientation->y;
	rotation[2] = vOrientation->z;
}

void Soldier::Update(const double& deltaTime) {
	float velocity = 100.0f * static_cast<float>(deltaTime);
	float shrinkRate = -5.0f * static_cast<float>(deltaTime);

	float x, y, z;
	Camera* camera = Scene::GetCamera();
	camera->GetEyePosition(x, y, z);

	// change gesture when win
	if (!ifWin && z < -700 && abs(y - (50)) < 20 && !_flagLose)
	{
		ifWin = true;
		_obj_path = "./Obj/" + _filename2 + ".obj";
		_tex_path = "./Textures/squid.bmp";


		objectFileReader = new ObjectFileReader(_obj_path);
		objectFileReader->Load();

		vertices = objectFileReader->vertices;
		normals = objectFileReader->normals;
		textureCoordinates = objectFileReader->textureCoordinates;
		faces = objectFileReader->faces;
		faceMaterials = objectFileReader->faceMaterials;

		_texID = scene->GetTexture(_tex_path);

		pos[0] = 1.5 * pos[0];
	}

	// r will reset transformation values
	if (_flagReset)
	{
		ifWin = false;
		_obj_path = "./Obj/" + _filename + ".obj";
		_tex_path = "./Textures/squid.bmp";

		objectFileReader = new ObjectFileReader(_obj_path);
		objectFileReader->Load();

		vertices = objectFileReader->vertices;
		normals = objectFileReader->normals;
		textureCoordinates = objectFileReader->textureCoordinates;
		faces = objectFileReader->faces;
		faceMaterials = objectFileReader->faceMaterials;

		_texID = scene->GetTexture(_tex_path);
		size(vSize->x, vSize->y, vSize->z);
		position(vPosition->x, vPosition->y, vPosition->z);
		orientation(vOrientation->x, vOrientation->y, vOrientation->z);
		_flagReset = false;
	}

	
}


void Soldier::HandleKey(unsigned char key, int state, int x, int y)
{

	switch (key)
	{
	
	case 'b':
	case 'B':
		_flagReset = true;
		break;

	}
}

void Soldier::HandleSpecialKey(int key, int state, int x, int y)
{


}