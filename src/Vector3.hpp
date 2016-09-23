#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3 {
public: 
	double x; 
	double y; 
	double z; 

	Vector3(double x_in = 0, double y_in = 0, double z_in = 0) : x(x_in), y(y_in), z(z_in) {}
	double magnitude(); 
	Vector3 normalize(); 
	Vector3 cross(Vector3 v); 
	double dot(Vector3 v); 
}; 

#endif 