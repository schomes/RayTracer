#include "Material.hpp"

Material::Material(RGB diffuseColor_in, RGB specularColor_in, double ka_in, double kd_in, double ks_in, double shininess_in) {
	diffuseColor = diffuseColor_in; 
	specularColor = specularColor_in; 
	ka = ka_in; 
	kd = kd_in; 
	ks = ks_in; 
	shininess = shininess_in; 
}


// void Material::setMaterialColor(const RGB &color) {
// 	materialColor = color; 
// }