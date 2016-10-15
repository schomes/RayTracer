#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include "Camera.hpp"

class Perspective : public Camera {
private: 

public: 
	Perspective() {}

	Ray getRay(int x, int y);

}; 

#endif