#ifndef SURFACE_H
#define SURFACE_H

#include "Point3.hpp"
#include "Vector3.hpp"
#include "Material.hpp"
#include "Image.hpp"
#include "Ray.hpp"

// This class represents any surface that can be hit by a ray.
class Surface {
protected: 
	Point3 center;
	Material material; 
	Image *texture = NULL; 

public: 
	Surface(){}

	// Accessor methods 
	const Point3 & getCenter() const {return center;}
	Material getMaterial() {return material;} 
	
	// Mutator methods
	void setMaterial(Material &material_in) {material = material_in;}
	void setTexture(Image *texture_in) {texture = texture_in;}

	virtual double hit(Ray &ray) = 0;  
	virtual Vector3 getNormalForPoint(Point3 &point) = 0; 
	virtual RGB getTextureColor(Point3 &p) = 0;
	// virtual Box bounding-box(); 
}; 

#endif 