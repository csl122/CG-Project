#pragma once
#include "DisplayableObject.h"

class Doors :
	public DisplayableObject
{
public:
	Doors() {};
	Doors(const std::string& filename);
	~Doors() {};

	void Display();

private:
	void DrawDoors();
	void drawCylinder(GLdouble r, GLdouble h);
	GLint texID;
};

