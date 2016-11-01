#ifndef CAMERA_H
#define CAMERA_H

#include "Point3.hpp"
#include "Vector3.hpp"
#include "Ray.hpp"
#include <vector> 

class Camera {
protected: 
	Point3 cameraPosition;
	Vector3 u, v, w; // Camera coordinate axes
	Point3 ul, ur, ll, lr; // Viewing window corners (upper-left, upper-right, lower-left, lower-right)
	Vector3 hOffset, vOffset; // Horizontal and vertical offsets per pixel 

public: 
	Camera(){}
	//Camera(Point3 cameraPosition, Vector3 viewDirection, Vector3 upDirection, int imageWidth, int imageHeight, double verticalFieldOfView); 

	// Accessor methods 
	Point3 getPosition() const {return cameraPosition;}

	// Mutator methods


	virtual Ray getRay(int x, int y) = 0; 
	virtual std::vector<Ray> getRayCluster(int x, int y, int numberOfJitters) = 0; 

}; 

#endif