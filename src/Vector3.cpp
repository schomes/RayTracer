#include "Vector3.hpp"
#include <cmath> 

double Vector3::magnitude() {
	double x2 = pow(x, 2.0);
	double y2 = pow(y, 2.0);
	double z2 = pow(z, 2.0);
	double len = sqrt(x2 + y2 + z2); 
	return len; 
}

Vector3 Vector3::normalize() {
	double length = this->magnitude(); 
	double newX = x / length; 
	double newY = y / length; 
	double newZ = z / length; 
	return Vector3(newX, newY, newZ); 

}

Vector3 Vector3::cross(Vector3 v) {
	double newX = (this->y * v.z) - (this->z * v.y); 
	double newY = (this->z * v.x) - (this->x * v.z); 
	double newZ = (this->x * v.y) - (this->y * v.x);
	return Vector3(newX, newY, newZ);  
}

double Vector3::dot(Vector3 v) {
	return (this->x * v.x) + (this->y * v.y) + (this->z * v.z); 
}