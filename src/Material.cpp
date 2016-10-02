#include "Material.hpp"

void Material::setDiffuseColor(RGB diffuseColor_in) {
	diffuseColor = diffuseColor_in;
} 

void Material::setSpecularColor(RGB specularColor_in) {
	specularColor = specularColor_in; 
}

void Material::setAmbientConstant(double ka_in) {
	ka = ka_in; 
}

void Material::setDiffuseConstant(double kd_in) {
	kd = kd_in; 
}

void Material::setSpecularConstant(double ks_in) {
	ks = ks_in; 
}

void Material::setShininess(double shininess_in) {
	shininess = shininess_in; 
}


// void Material::setMaterialColor(const RGB &color) {
// 	materialColor = color; 
// }