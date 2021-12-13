#include "MyScene.h"
#include "Turntable.h"
#include "Triangle.h"
#include "Floor.h"
#include "Wall.h"
#include "TimeTunnel.h"
#include "Framework.h"
#include "Swing.h"
#include "Slider.h"
#include "Doors.h"
#include "Triforce.h"
#include "ModelObject.h"
#include "Soldier.h"

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
	Turntable* l = new Turntable();
	Framework* fw = new Framework();
	Swing* sw = new Swing();
	Slider* sl = new Slider();
	Doors* dr = new Doors();
	Triforce* tf = new Triforce();
	f->size(100.0f);
	r->size(100.0f);
	w->size(100.0f);
	t->size(0.5f);
	tt->size(100.0f);
	l->size(5.0f);
	l->position(-700, -80, -500);
	fw->size(1.2f);
	fw->position(-1000, -110, 800);
	sw->size(1.0f);
	sw->position(800, -110, -400);
	sl->size(0.9f);
	sl->position(560, -90, 470);
	dr->size(1.f);
	dr->position(0, 80, -1100);
	tf->size(1.f);
	tf->position(0,20, 0);



AddObjectToScene(dr);
	AddObjectToScene(l);
	AddObjectToScene(f);
	AddObjectToScene(t);
	AddObjectToScene(w);
	AddObjectToScene(r);
	AddObjectToScene(tt);
	AddObjectToScene(fw);
	AddObjectToScene(sw);
	AddObjectToScene(sl);
	//AddObjectToScene(tf);
	


	Vertex* objScale = new Vertex(35, 35, 35);
	Vertex* soldierP = new Vertex(-300, -100, -1000);
	Soldier* soldier = new Soldier(this, "squid", "soldierLeft", new Vertex(.3f, .3f, .4f), GL_CCW);
	soldier->setScale(objScale);
	soldier->setPosition(soldierP);
	soldier->setOrientation(new Vertex(0, 180, 0));
	AddObjectToScene(soldier);


	Vertex* soldier2P = new Vertex(300, -100, -1000);
	Soldier* soldier2 = new Soldier(this, "squid", "soldierRight", new Vertex(.3f, .3f, .4f), GL_CCW);
	soldier2->setScale(objScale);
	soldier2->setPosition(soldier2P);
	soldier2->setOrientation(new Vertex(0, 180, 0));
	AddObjectToScene(soldier2);

}

/// set the perspective of camera
void MyScene::Projection()
{
    GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
    gluPerspective(60.0, aspect, 1.0, 5000.0);
}
