#pragma once
#include "DisplayableObject.h"

class Floor :
	public DisplayableObject
{
public:
	Floor(){};
	Floor(const std::string& filename, int floortype);
	~Floor(){};

	void Display();

private:
	void DrawSand();
	void DrawPath();
	GLint texID;
	int type;
};

