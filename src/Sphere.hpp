#ifndef SPHERE_H
#define SPHERE_H

#include "Surface.hpp"
#include "Point3.hpp"
#include "Vector3.hpp"
#include "Material.hpp"
#include "Ray.hpp"

class Sphere : public Surface {
private: 
	double radius; 
	
public: 
	Sphere() {} 
	Sphere(Point3 center_in, double radius_in) {center=center_in; radius=radius_in;}
	 
	double hit(Ray &ray);
	Vector3 getNormalForPoint(Point3 &point); 
}; 

#endif 