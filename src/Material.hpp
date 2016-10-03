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
	void setDiffuseColor(RGB diffuseColor_in); 
	void setSpecularColor(RGB specularColor_in); 
	void setAmbientConstant(double ka_in); 
	void setDiffuseConstant(double kd_in); 
	void setSpecularConstant(double ks_in); 
	void setShininess(double shininess_in); 

	// TODO: remove constructor and create setter/getter methods instead
	// This makes it easier to add more material features in the future (now we don't have to extend the constructor even more!)
	// Also, this method will allow code to be cleaner; lines won't get very long, and each line can be associated with one aspect of a material

//	void setMaterialColor(const RGB &color); 
	//RGB getMaterialColor() {return diffuseColor;}
	RGB getDiffuseColor() {return diffuseColor;}
	RGB getSpecularColor() {return specularColor;}
	double getAmbientConstant() {return ka;}
	double getDiffuseConstant() {return kd;}
	double getSpecularConstant() {return ks;}
	double getShininess() {return shininess;}
}; 

#endif 