#ifndef ELLIPSOID
#define ELLIPSOID

#include "Surface.hpp"
#include "Point3.hpp"
#include "Material.hpp"
#include "Ray.hpp"

class Ellipsoid : public Surface {
private:
  double aRadius;
  double bRadius;
  double cRadius;

public:
  Ellipsoid() {}
  Ellipsoid(Point3 center_in, double aRadius_in, double bRadius_in, double cRadius_in) {
    center = center_in;
    aRadius = aRadius_in;
    bRadius = bRadius_in;
    cRadius = cRadius_in;
  }

  double hit(Ray &ray);
  Vector3 getNormalForPoint(Point3 &point); 

}; 

#endif
