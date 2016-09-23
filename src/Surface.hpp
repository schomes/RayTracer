#ifndef SURFACE_H
#define SURFACE_H

#include "Point3.hpp"

class Surface {
private: 
	Point3 _center;
	// prevent construction of base class
	Surface(){}

protected: 
	Surface(Point3 center_in) : _center(center_in) {}
	 

public: 
	const Point3 & getCenter() const {return _center;}
	//virtual bool hit(); 
	// virtual Box bounding-box(); 

}; 

#endif 