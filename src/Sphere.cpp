#include "Sphere.hpp"
#include "Point3.hpp"
#include <cmath> 

double Sphere::hit(Ray &ray) {

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
	double A = pow((x0 - xc), 2.0) + pow((y0 - yc), 2.0) + pow((z0 - zc), 2.0) - pow(radius, 2.0); 




}