#ifndef ORTHOGRAPHIC_H
#define ORTHOGRAPHIC_H

#include "Camera.hpp"

class Orthographic : public Camera {
private: 

public: 
	Orthographic() {}
	Orthographic(Point3 cameraPosition, Vector3 viewDirection, Vector3 upDirection, int imageWidth, int imageHeight, double verticalFieldOfView);

	Ray getRay(int x, int y);

}; 

#endif