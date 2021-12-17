#pragma once
#include "WorldObject.h"
#include "Face.h"
#include "Functions.h"
#include "ObjectFileReader.h"

class Timer :
	public WorldObject
{
public:
	Timer(MyScene* scene, string filePath, Vertex* color, int winding);
	~Timer();
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
	bool ifWin;
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
	GLboolean _flagMove, _flagLose;

	GLfloat* _mat_ambient, * _mat_diffuse, * _mat_specular, * _mat_shininess;
};





//#pragma once
//
//#include "DisplayableObject.h"
//#include "Animation.h"
//#include "Input.h"
//
//class Timer :
//	public DisplayableObject,
//	public Animation,
//	public Input
//{
//public:
//	Timer();
//	~Timer() {};
//
//	void Display();
//	void Update(const double& deltaTime);
//	void HandleKey(unsigned char key, int state, int x, int y);
//
//	void HandleSpecialKey(int key, int state, int x, int y) {}
//	void HandleMouse(int button, int state, int x, int y) {}
//	void HandleMouseDrag(int x, int y) {}
//	void HandleMouseMove(int x, int y) {}
//
//	string _tex_path;
//	string _obj_path;
//
//private:
//	float xrot, yrot, zrot;
//	float scale;
//	bool _flagReset;
//	float animateTime;          // variable to store the current time the animation has run for
//	float animateRotation;      // variable to track the current amount of rotation steps
//	int keyframe;
//	float interpTime;
//	
//};