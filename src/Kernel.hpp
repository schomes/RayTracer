#ifndef KERNEL_H
#define KERNEL_H

#include <fstream> 
#include "Point3.hpp"

// The kernel is responsible for rendering routines and scene reading. 
class Kernel {
public: 

	Point3 cameraPosition; 
// PUBLIC
	void readScene(std::ifstream &inputFile); 


}; 



#endif 