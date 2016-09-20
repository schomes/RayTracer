#ifndef SURFACE_H
#define SURFACE_H

class Surface {
private: 
	// prevent construction of base class
	Surface(){}

public: 
	virtual bool hit(); 
	// virtual Box bounding-box(); 

}; 

#endif 