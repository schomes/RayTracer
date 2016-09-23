#ifndef SURFACE_H
#define SURFACE_H

#include "Point3.hpp"
#include "Material.hpp"
#include "Ray.hpp"

class Surface {
private: 
	Point3 _center;
	Material _material; 
	// prevent construction of base class
	Surface(){}

protected: 
	Surface(Point3 center_in) : _center(center_in) {}
	 

public: 
	const Point3 & getCenter() const {return _center;}
	Material getMaterial() {return _material;}
	void setMaterial(Material &material) {_material = material;}
	virtual double hit(Ray &ray) {return -2.0;} 
	// virtual Box bounding-box(); 

}; 

#endif 