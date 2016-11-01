#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include "Camera.hpp"
#include <vector> 

class Perspective : public Camera {
private: 

public: 
	Perspective() {}
	Perspective(Point3 cameraPosition, Vector3 viewDirection, Vector3 upDirection, int imageWidth, int imageHeight, double verticalFieldOfView, double distance = 15.0);

	Ray getRay(int x, int y);
	std::vector<Ray> getRayCluster(int x, int y, int numberOfJitters); 

}; 

#endif