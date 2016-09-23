#ifndef MATERIAL_H
#define MATERIAL_H

#include "RGB.hpp"

class Material {
private: 
	RGB materialColor; 

public: 
	void setMaterialColor(const RGB &color); 
}; 

#endif 