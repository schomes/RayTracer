#ifndef LIGHT_H
#define LIGHT_H

#include "HVector.hpp"
#include "RGB.hpp"

class Light {
private: 
	HVector position; 
	RGB color; 
public: 
	Light(HVector position_in, RGB color_in) : position(position_in), color(color_in) {}

	HVector getPosition() {return position;}
	RGB getColor() {return color;}
 
}; 

#endif