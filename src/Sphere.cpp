#include "Sphere.hpp"
#include "Point3.hpp"
#include <cmath> 

#include <iostream> 

double Sphere::hit(Ray &ray) {

	std::cout << "entered" << std::endl; 
	// for equation At^2 + Bt + c = 0

	double x0 = (ray.origin).x; 
	double y0 = (ray.origin).y; 
	double z0 = (ray.origin).z; 

	double xd = (ray.direction).x;
	double yd = (ray.direction).y;
	double zd = (ray.direction).z;

	Point3 center = getCenter(); 
	double xc = center.x;
	double yc = center.y;
	double zc = center.z;

	double B = 2 * (xd * (x0 - xc) + yd * (y0 - yc) + zd * (z0 - zc)); 
	double C = pow((x0 - xc), 2.0) + pow((y0 - yc), 2.0) + pow((z0 - zc), 2.0) - pow(radius, 2.0); 

	double discriminant = sqrt(pow(B, 2.0) - (4 * C)); 

	if (discriminant < 0) {
		return -1.0; 
	} else {
		double result1 = (-B + discriminant) / 2; 
		double result2 = (-B - discriminant) / 2; 

		double minValue = fmin(result1, result2); 
		if (minValue < 0) { 
			return fmax(result1, result2); 
		}
		return minValue; 
	}
}