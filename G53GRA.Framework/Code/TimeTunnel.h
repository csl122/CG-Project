#pragma once
#include "DisplayableObject.h"
#include "Animation.h"

class TimeTunnel :
	public DisplayableObject,
	public Animation

{
public:
	TimeTunnel() {};
	TimeTunnel(const std::string& filename);
	~TimeTunnel() {};

	void Display();
	void Update(const double& deltaTime);

private:

	GLint texID;
};

