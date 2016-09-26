#ifndef SURFACE_H
#define SURFACE_H

#include "Point3.hpp"
#include "Material.hpp"
#include "Ray.hpp"

/// This class represents a surface
class Surface {
protected: 
	Point3 center;
	Material material; 

public: 
	Surface(){}

	// Accessor methods 
	const Point3 & getCenter() const {return center;}
	Material getMaterial() {return material;}
	
	// Mutator methods
	void setMaterial(Material &material_in) {material = material_in;}

	virtual double hit(Ray &ray) = 0;  
	// virtual Box bounding-box(); 
}; 

#endif 