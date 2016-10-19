#include "Sphere.hpp"
#include "Point3.hpp"
#include <cmath> 

#define NO_COLLISION_FLAG -1.0

double Sphere::hit(Ray &ray) {

	// Ray origin 
	double x0 = (ray.origin).x; 
	double y0 = (ray.origin).y; 
	double z0 = (ray.origin).z; 

	// Ray direction 
	double xd = (ray.direction).x;
	double yd = (ray.direction).y;
	double zd = (ray.direction).z;

	// Sphere center 
	Point3 center = getCenter(); 
	double xc = center.x;
	double yc = center.y;
	double zc = center.z;

	// Variables represent components of the equation At^2 + Bt + C = 0
	double A = pow(xd, 2.0) + pow(yd, 2.0) + pow(zd, 2.0); 
	double B = 2 * (xd * (x0 - xc) + yd * (y0 - yc) + zd * (z0 - zc)); 
	double C = pow((x0 - xc), 2.0) + pow((y0 - yc), 2.0) + pow((z0 - zc), 2.0) - pow(radius, 2.0); 

	double discriminant = pow(B, 2.0) - (4 * A * C); 

	if (discriminant < 0) {
		return NO_COLLISION_FLAG; 
	} 
	else {
		double result1 = (-B + sqrt(discriminant)) / 2.0 * A; 
		double result2 = (-B - sqrt(discriminant)) / 2.0 * A;  

		// Return the smallest positive value
		double minValue = fmin(result1, result2); 
		if (minValue < 0) { 
			// Return the other value instead 
			return fmax(result1, result2); 
		} 
		return minValue; 
	}
}

Vector3 Sphere::getNormalForPoint(Point3 &point) {
	return (point - center) / radius; 
}

RGB Sphere::getTextureColor(Point3 &p) {

	if (texture) {

		double normalX = (p.x - center.x) / radius; 
		double normalY = (p.y - center.y) / radius; 
		double normalZ = (p.z - center.z) / radius; 

		// Align the polls with the y-axis
		double phi = acos(-normalY); 
		double theta = atan2(normalX, -normalZ); 

		double pi = 4 * atan(1.0);
		double u = (theta + pi) / (2 * pi);
		double v = phi / pi;  

		int i = u * (double)(texture->getWidth() - 1); 
		int j = v * (double)(texture->getHeight() - 1); 

		RGB color = texture->getPixel((texture->getWidth() - i), j);
		color.r = color.r / 255.0; 
		color.g = color.g / 255.0;
		color.b = color.b / 255.0;

		return color; 
	} else {
		return material.getDiffuseColor(); 
	}

}