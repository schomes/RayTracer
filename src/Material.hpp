#ifndef MATERIAL_H
#define MATERIAL_H

#include "RGB.hpp"

class Material {
private: 
	RGB diffuseColor;
	RGB specularColor; 

	// Reflection constants
	double ka; // Ambient
	double kd; // Diffuse
	double ks; // Specular

	double shininess; 

public: 
	Material(RGB diffuseColor_in, RGB specularColor_in, double ka_in, double kd_in, double ks_in, double shininess_in);

	// TODO: remove constructor and create setter/getter methods instead
	// This makes it easier to add more material features in the future (now we don't have to extend the constructor even more!)
	// Also, this method will allow code to be cleaner; lines won't get very long, and each line can be associated with one aspect of a material

//	void setMaterialColor(const RGB &color); 
	RGB getMaterialColor() {return diffuseColor;}
}; 

#endif 