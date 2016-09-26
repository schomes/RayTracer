#ifndef SPHERE_H
#define SPHERE_H

#include "Surface.hpp"
#include "Point3.hpp"
#include "Material.hpp"
#include "Ray.hpp"

class Sphere : public Surface {
private: 
	double radius; 
	Point3 center;
	Material material; 

public: 
	Sphere() {} 
	Sphere(Point3 center_in, double radius_in) : center(center_in), radius(radius_in) {}
	
	// Accessor methods 
	const Point3 & getCenter() const {return center;}
	Material getMaterial() {return material;}
	
	// Mutator methods
	void setMaterial(Material &material_in) {material = material_in;}

	double hit(Ray &ray);
}; 

#endif 