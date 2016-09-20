#ifndef KERNEL_H
#define KERNEL_H

#include <fstream> 
#include "Point3.hpp"
#include "Vector3.hpp"
#include "RGB.hpp"

// The kernel is responsible for rendering routines and scene reading. 
class Kernel {
public: 
	Point3 cameraPosition; 
	Vector3 viewingDirection; 
	Vector3 upDirection; 
	double verticalFieldOfView; // in degrees 
	int width; 
	int height; 
	RGB bkgcolor; 
	RGB materialColor; 


// PUBLIC
	void readScene(std::ifstream &inputFile); 


}; 



#endif 