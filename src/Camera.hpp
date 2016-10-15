#ifndef CAMERA_H
#define CAMERA_H

#include "Point3.hpp"
#include "Vector3.hpp"
#include "Ray.hpp"

class Camera {
private: 
	Point3 cameraPosition;
	Vector3 u, v, w


public: 
	Camera(){}

	// Accessor methods 
	Point3 getPosition() const {return cameraPosition;}

	// Mutator methods

	
	virtual Ray getRay(int x, int y) = 0; 

}; 

#endif