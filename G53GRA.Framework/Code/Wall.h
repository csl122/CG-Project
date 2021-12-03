#pragma once
#include "DisplayableObject.h"

class Wall :
	public DisplayableObject
{
public:
	Wall() {};
	Wall(const std::string& filename, int walltype);
	~Wall() {};

	void Display();

private:
	void DrawWall();
	void DrawCloudWall();
	GLint texID;
	int type;
};

