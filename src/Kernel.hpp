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
#include "Triangle.hpp"
#include "Material.hpp"
#include "Light.hpp"
#include "Image.hpp"

#define PERSPECTIVE_TYPE 0
#define ORTHOGRAPHIC_TYPE 1

// The kernel is responsible for rendering routines and scene reading.
class Kernel {
private:
	RGB TraceRay(Ray &ray);
	RGB ShadeRay(Point3 &point, Surface *object);
	double findShadow(Ray &ray, Light &light); 
	double isInShadow(Ray &ray, std::vector<Surface*> &objects, Light &light); 

public:
	int cameraType = PERSPECTIVE_TYPE; 
	Point3 cameraPosition;
	Vector3 viewingDirection;
	Vector3 upDirection;
	double verticalFieldOfView; // in degrees
	int width;
	int height;
	RGB bkgcolor;
	Material *material;
	std::vector<Image> textures;
	std::vector<Surface*> objects;
	std::vector<Point3> vertices;
	std::vector<Vector3> perVertexSurfaceNormals;
	std::vector<Vector3> textureCoordinates; 
	std::vector<Light> lights; 

	void readScene(std::ifstream &inputFile);
	Image render();

};



#endif
