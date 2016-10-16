#include "Triangle.hpp"

#define NO_COLLISION_FLAG -1.0

double Triangle::hit(Ray &ray) {

	// Ray origin 
	double x0 = (ray.origin).x; 
	double y0 = (ray.origin).y; 
	double z0 = (ray.origin).z; 

	// Ray direction 
	double xd = (ray.direction).x;
	double yd = (ray.direction).y;
	double zd = (ray.direction).z;
	
	// Get vertices from vertex array 
	Point3 v0 = vertexArray->at(p0 - 1); 
	Point3 v1 = vertexArray->at(p1 - 1);
	Point3 v2 = vertexArray->at(p2 - 1);

	// Calculate vectors e1, e2 and n
	Vector3 e1 = v1 - v0; 
	Vector3 e2 = v2 - v0; 
	Vector3 n = e1.cross(e2); 

	// Variables represent components of the plane equation Ax + By + Cz + D = 0
	double A = n.x; 
	double B = n.y; 
	double C = n.z; 
	double D = -(A*(v0.x) + B*(v0.y) + C*(v0.z)); 

	// Calculate the numerator and denominator separately in case the denominator is zero
	double numerator = -((A * x0) + (B * y0) + (C * z0) + D); 
	double denominator = (A * xd) + (B * yd) + (C * zd); 

	if (denominator == 0) {
		return NO_COLLISION_FLAG; 
	}
	else {
		double t = numerator / denominator; 
		return t; 
	}
}

Vector3 Triangle::getNormalForPoint(Point3 &point) {
	return Vector3(0, 0, 0); 
}