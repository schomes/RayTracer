#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include "Camera.hpp"

class Perspective : public Camera {
private: 

public: 
	Perspective() {}
	Perspective(Point3 cameraPosition, Vector3 viewDirection, Vector3 upDirection, int imageWidth, int imageHeight, double verticalFieldOfView); 

	Ray getRay(int x, int y);

}; 

#endif