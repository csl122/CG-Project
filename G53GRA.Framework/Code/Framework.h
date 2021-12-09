#pragma once
#include "DisplayableObject.h"

class Framework :
	public DisplayableObject
{
public:
	Framework() {};
	Framework(const std::string& filename);
	~Framework() {};

	void Display();

private:
	void DrawFramework();
	void drawCylinder(GLdouble r, GLdouble h);
	GLint texID;
};

