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