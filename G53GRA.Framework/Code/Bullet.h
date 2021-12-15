#pragma once
#include "WorldObject.h"
#include "Face.h"
#include "Functions.h"
#include "ObjectFileReader.h"

class Bullet :
	public WorldObject
{
public:
	Bullet(MyScene* scene, Vertex* color, int winding);
	~Bullet();
	void Display();
	void Update(const double& deltaTime);

	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);

	void setScale(Vertex* size);
	void setPosition(Vertex* position);
	void setOrientation(Vertex* orientation);
	static void Bullet::SetLose(bool flag);

	Vertex* vSize;
	Vertex* vPosition;
	Vertex* vOrientation;

	MyScene* scene;

	vector<Vertex*> vertices;
	vector<Vertex*> normals;
	vector<Face*> faces;
	vector<float*> textureCoordinates;
	vector<int> faceMaterials;

	Vertex* tempV;
	Vertex* defaultColor;

	ObjectFileReader* objectFileReader;
	string _obj_path;
	string _tex_path;
	string _tex_path2;
	string _filename;
	string _filename2;
	bool ifWin;
	static bool _flagLose;

	int _texID;
	int _texID2;
	float currentx;
	float currentz;

	float animateTime;          // variable to store the current time the animation has run for
	float animateRotation;      // variable to track the current amount of rotation steps

	void Render();
private:

	void RenderFace(Face* face);
	void RenderVertex(int vertexIndex);
	void RenderNormal(int normalIndex);
	void RenderMaterial(int textureIndex);

	GLboolean _iKey, _jKey, _kKey, _lKey, _oKey, _uKey;
	GLboolean _plusKey, _minusKey, _upKey, _downKey, _leftKey, _rightKey, _pageUp, _pageDn;
	GLboolean _flagReset, _flagAutospin;

	GLfloat* _mat_ambient, * _mat_diffuse, * _mat_specular, * _mat_shininess;
};
