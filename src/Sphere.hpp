#ifndef SPHERE_H
#define SPHERE_H

#include "Surface.hpp"
#include "Ray.hpp"

class Sphere : public Surface {
private: 
	double radius; 

public: 
	Sphere(); 
	Sphere(Point3 center_in, double radius_in) : Surface(center_in), radius(radius_in) {}
	double hit(Ray &ray);
}; 

#endif 