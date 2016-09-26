#include <cmath>
#include "Kernel.hpp"
#include <iostream>
#include <sstream> /* string streams */
#include <stdlib.h> /* exit, EXIT_FAILURE */
#include "Point3.hpp"
#include "Ray.hpp"
#include "RGB.hpp"
// #include "Sphere.hpp"

#define MAX_COLOR_VALUE 255 // maximum value for an RGB component
#define FAR_CLIP 1000.0 // maximum distance to consider ray collision

void Kernel::readScene(std::ifstream &inputFile) {
	if (inputFile.is_open()) {
		std::string line = "";
		while(std::getline(inputFile, line)) {

			std::stringstream ss(line);
			std::string variable = "";
			ss >> variable;

			if (variable == "eye") {
				double x = 0.0, y = 0.0, z = 0.0;
				ss >> x >> y >> z;
				cameraPosition = Point3(x, y, z);
			}

			else if (variable == "viewdir") {
				double x = 0.0, y = 0.0, z = 0.0;
				ss >> x >> y >> z;
				viewingDirection = Vector3(x, y, z);
			}

			else if (variable == "updir") {
				double x = 0.0, y = 0.0, z = 0.0;
				ss >> x >> y >> z;
				upDirection = Vector3(x, y, z);
			}

			else if (variable == "fovv") {
				double fovv = 0.0; // in degrees
				ss >> fovv;
				verticalFieldOfView = fovv;
			}

			else if (variable == "imsize") {
				int width_in, height_in;
				ss >> width_in >> height_in;
				width = width_in;
				height = height_in;
			}

			else if (variable == "bkgcolor") {
				double r, g, b;
				ss >> r >> g >> b;
				// convert colors in range 0 - 1 to range 0 - 255
				bkgcolor = RGB((int)(MAX_COLOR_VALUE * r), (int)(MAX_COLOR_VALUE * g), (int)(MAX_COLOR_VALUE * b));
			}

			else if (variable == "mtlcolor") {
				double r, g, b;
				ss >> r >> g >> b;
				// convert colors in range 0 - 1 to range 0 - 255
				RGB materialColor = RGB((int)(MAX_COLOR_VALUE * r), (int)(MAX_COLOR_VALUE * g), (int)(MAX_COLOR_VALUE * b));

				std::cout << material << std::endl;

				Material *m = new Material();
				m->setMaterialColor(materialColor);
				material = m;
			}

			else if (variable == "sphere") {
				double x, y, z, r;
				ss >> x >> y >> z >> r;
				// Check if a material exists
				if (material) {
					Sphere *s = new Sphere(Point3(x, y, z), r);
					s->setMaterial(*material);
					objects.push_back(s);
				} else {
					std::cerr << "Error: No material was specified before defining a sphere." << std::endl;
					exit(EXIT_FAILURE);
				}

			}

			else if (variable.find_first_not_of (' ') == variable.npos) {
				continue;
			}

			else {
				std::cerr << "Error: Invalid input file." << std::endl;
				exit(EXIT_FAILURE);
			}


		}
	}
}

Image Kernel::render() {

	// Initialize output image
	// TODO: check if height, width are valid
	Image img = Image(width, height);

	// Determine camera coordinate axes
	//... u is orthogonal to the viewingDirection
	//... v is orthogonal to the viewingDirection and u
	Vector3 w, u, v;
	//...TODO: check if viewingDirection and upDirection are close to parallel
	//...TODO cont'd: more parallel means cross is closer to (0, 0, 0) (slide 6 - raycasting02.pdf)
    w = viewingDirection.normalize();
	u = upDirection.cross(w);
	u = u.normalize();
	v = w.cross(u);
	v = v.normalize();

	// Unit vector in the viewing direction
	Vector3 n = viewingDirection.normalize();

	// Determine corners of viewing window
	double aspectRatio = (double)(width) / height;
	double d = 15.0; // d is arbitrarily chosen
	double pi = 4 * atan(1.0);
	double radians = ((verticalFieldOfView / 2.0) * pi) / 180.0;
	double viewHeight = 2 * d * tan(radians);
	double viewWidth = aspectRatio * viewHeight;
	//... Viewing window corners
	Point3 ul = cameraPosition + (d * n) + (viewHeight / 2 * v) - (viewWidth / 2 * u);
	Point3 ur = cameraPosition + (d * n) + (viewHeight / 2 * v) + (viewWidth / 2 * u);
	Point3 ll = cameraPosition + (d * n) - (viewHeight / 2 * v) - (viewWidth / 2 * u);
	Point3 lr = cameraPosition + (d * n) - (viewHeight / 2 * v) + (viewWidth / 2 * u);

	// Horizontal offset per pixel
	Vector3 hOffset = (ur - ul) / (width - 1.0);
	// Vertical offset per pixel
	Vector3 vOffset = (ll - ul) / (height - 1.0);


	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
			Point3 viewingWindowPoint = ul + (vOffset * row) + (hOffset * column);
			Vector3 rayDirection = viewingWindowPoint - cameraPosition;
			rayDirection = rayDirection.normalize();
			Ray ray = Ray(cameraPosition, rayDirection);

			RGB color = TraceRay(ray);
			img.setPixel(color, column, row);
		}
	}

	return img;

}

RGB Kernel::TraceRay(Ray &ray) {

	RGB color = bkgcolor;

	// For each object in the scene, check for intersection with ray
	Surface *object;
	double minT = FAR_CLIP;
	// for each object, check if a ray hits it
	for (int index = 0; index < objects.size(); index++) {
		Surface *testObject = objects.at(index);
		double tempMinT = testObject->hit(ray);

		if ((tempMinT > 0) && (tempMinT < minT)) {
			object = testObject;
			minT = tempMinT;
		}
	}

	// We didn't hit anything in front of us, so return background color
	if (minT == FAR_CLIP) {
		return color;
	} else {
		Point3 shadingCoordinate = ray.origin + (minT * ray.direction);
		return ShadeRay(shadingCoordinate, object);
	}
}

RGB Kernel::ShadeRay(Point3 point, Surface *object) {
	Material material = object->getMaterial();
	return material.getMaterialColor();
}
