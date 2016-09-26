#ifndef SURFACE_H
#define SURFACE_H

#include "Point3.hpp"
#include "Material.hpp"
#include "Ray.hpp"

/// This class represents a surface
class Surface {
public: 
	Surface(){}
	virtual double hit(Ray &ray) = 0;  
	// virtual Box bounding-box(); 
}; 

#endif 