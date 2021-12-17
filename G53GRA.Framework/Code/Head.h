#pragma once
#include "WorldObject.h"
#include "Face.h"
#include "Functions.h"
#include "ObjectFileReader.h"

class Head :
	public WorldObject
{
public:
	Head(MyScene* scene, string filePath, Vertex* color, int winding);
	~Head();
	void Display();
	void Update(const double& deltaTime);

	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);

	void setScale(Vertex* size);
	void setPosition(Vertex* position);
	void setOrientation(Vertex* orientation);

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
	static bool ifWin;
	static bool _flagStart;

	int _texID;
	int _texID2;


	void Render();
private:

	void RenderFace(Face* face);
	void RenderVertex(int vertexIndex);
	void RenderNormal(int normalIndex);
	void RenderMaterial(int textureIndex);
	int keyframe;               // variable to track which keyframe we are on
	float animateTime;          // variable to store the current time the animation has run for
	float animateRotation;      // variable to track the current amount of rotation steps
	float interpA;              // variable to hold what the first keyframe angle is
	float interpB;
	float interpTime;

	GLboolean _iKey, _jKey, _kKey, _lKey, _oKey, _uKey;
	GLboolean _plusKey, _minusKey, _upKey, _downKey, _leftKey, _rightKey, _pageUp, _pageDn;
	GLboolean _flagReset, _flagAutospin;
	GLboolean _flagMove, _flagLose ;

	GLfloat* _mat_ambient, * _mat_diffuse, * _mat_specular, * _mat_shininess;
};
