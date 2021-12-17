#pragma once
#include "DisplayableObject.h"
#include "Animation.h"

class Light :
	public DisplayableObject,
	public Animation

{
public:
	Light() {};
	Light(const std::string& filename);
	~Light() {};

	void Display();
	void Update(const double& deltaTime);

private:

	GLint texID;
};

