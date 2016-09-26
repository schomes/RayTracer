#include "Ellipsoid.hpp"
#include <cmath>

#define NO_COLLISION_FLAG -1.0

double Ellipsoid::hit(Ray &ray) {

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

  double A = (pow(bRadius, 2.0) * pow(cRadius, 2.0) * pow(xd, 2.0)) + (pow(aRadius, 2.0) * pow(cRadius, 2.0) * pow(yd, 2.0)) + (pow(aRadius, 2.0) * pow(bRadius, 2.0) * pow(zd, 2.0));
  double B = 2 * ((pow(bRadius, 2.0) * pow(cRadius, 2.0) * xd * x0)) + ((pow(aRadius, 2.0) * pow(cRadius, 2.0) * yd * y0)) + ((pow(aRadius, 2.0) * pow(bRadius, 2.0) * zd * z0));
  double C = (pow(x0, 2.0) * pow(bRadius, 2.0) * pow(cRadius, 2.0)) + (pow(y0, 2.0) * pow(aRadius, 2.0) * pow(cRadius, 2.0)) + (pow(z0, 2.0) * pow(aRadius, 2.0) * pow(bRadius, 2.0)) - 1.0;

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

  return 0;

}
