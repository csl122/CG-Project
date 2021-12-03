#include "MyScene.h"

#include "Triangle.h"
#include "Floor.h"
#include "Wall.h"
#include "TimeTunnel.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight){}

void MyScene::Initialise()
{
	// set the background colour of the scene to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// DEMO 5
	// Show floor and triangle
#ifdef __APPLE__
	Floor* f = new Floor("./ground.bmp");
#else
	Floor* f = new Floor("./Textures/ground.bmp", 0);
	Floor* r = new Floor("./Textures/tunnelroad.bmp", 1);
	Wall* w = new Wall("./Textures/clwall.bmp", 1);
	TimeTunnel* tt = new TimeTunnel("./Textures/tunnel.bmp");
#endif
	//Floor *f = new Floor();
	
	Triangle *t = new Triangle();
	f->size(100.0f);
	r->size(100.0f);
	w->size(100.0f);
	t->size(0.5f);
	tt->size(100.0f);
	AddObjectToScene(f);
	AddObjectToScene(t);
	AddObjectToScene(w);
	AddObjectToScene(r);
	AddObjectToScene(tt);
}

/// set the perspective of camera
void MyScene::Projection()
{
    GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
    gluPerspective(60.0, aspect, 1.0, 5000.0);
}
