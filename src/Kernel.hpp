#ifndef KERNEL_H
#define KERNEL_H

#include <fstream>
#include <vector>
#include "Point3.hpp"
#include "Vector3.hpp"
#include "Ray.hpp"
#include "RGB.hpp"
#include "Surface.hpp"
#include "Sphere.hpp"
#include "Ellipsoid.hpp"
#include "Material.hpp"
#include "Light.hpp"
#include "Image.hpp"

// The kernel is responsible for rendering routines and scene reading.
class Kernel {
private:
	RGB TraceRay(Ray &ray);
	RGB ShadeRay(Point3 &point, Surface *object);
	double findShadow(Ray &ray, Light &light); 
	double isInShadow(Ray &ray, std::vector<Surface*> &objects, Light &light); 

public:
	Point3 cameraPosition;
	Vector3 viewingDirection;
	Vector3 upDirection;
	double verticalFieldOfView; // in degrees
	int width;
	int height;
	RGB bkgcolor;
	Material *material;
	std::vector<Surface*> objects;
	std::vector<Light> lights; 

	void readScene(std::ifstream &inputFile);
	Image render();

};



#endif
