#ifndef VECTOR3_H
#define VECTOR3_H

#include "Point3.hpp"

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

// Scalar, vector multiplication s * V
inline Vector3 operator * (double lhs, const Vector3 & rhs) {
	return Vector3(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs); 
}

// Scalar, vector multiplication V * s
inline Vector3 operator * (const Vector3 & lhs, double rhs) {
	return Vector3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs); 
}

// Point plus a vector
inline Point3 operator + (const Point3 & lhs, const Vector3 & rhs) {
	return Point3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); 
}

inline Point3 operator - (const Point3 & lhs, const Vector3 & rhs) {
	return Point3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); 
}

#endif 