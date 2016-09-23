#ifndef RAY_H 
#define RAY_H

#include "Vector3.hpp"
#include "Point3.hpp"

class Ray {
public: 
	Point3 origin; 
	Vector3 direction; 
	Ray(Point3 &p, Vector3 &v) : origin(p), direction(v) {}
}; 

#endif 