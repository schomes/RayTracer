#include <cmath>
#include <random> /* For random jitter when creating soft shadows */
#include "Kernel.hpp"
#include <iostream>
#include <sstream> /* string streams */
#include <stdlib.h> /* exit, EXIT_FAILURE */
#include "Point3.hpp"
#include "HVector.hpp"
#include "Ray.hpp"
#include "RGB.hpp"
#include "Perspective.hpp"

#define MAX_COLOR_VALUE 255 // maximum value for an RGB component
#define FAR_CLIP 1000.0 // maximum distance to consider ray collision
#define SHADOW_RAY_INTERSECTION_THRESHOLD 0.01 // Used to reject spurious self-intersections when detecting shadows
#define POSITIONAL_LIGHT_SOURCE_TYPE 1 // Positional light source

double clamp(double number, double min, double max) {
	return std::max(min, std::min(number, max));
}

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
				if (fovv >= 180.0) {
					std::cerr << "Error: Field of view must be smaller than 180 degrees." << std::endl;
					exit(EXIT_FAILURE);
				}
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

				r = clamp(r, 0.0, 1.0);
				g = clamp(g, 0.0, 1.0);
				b = clamp(b, 0.0, 1.0);
				bkgcolor = RGB(r, g, b);
			}

			// Material
			else if (variable == "mtlcolor") {
				// Diffuse color
				double diffuse_r, diffuse_g, diffuse_b;
				// Specular color
				double specular_r, specular_g, specular_b; 
				// Reflection constants
				double ka, kd, ks; 
				// Shininess constant
				double n; 

				ss >> diffuse_r >> diffuse_g >> diffuse_b; 
				ss >> specular_r >> specular_g >> specular_b; 
				ss >> ka >> kd >> ks; 
				ss >> n; 

				diffuse_r = clamp(diffuse_r, 0.0, 1.0);
				diffuse_g = clamp(diffuse_g, 0.0, 1.0);
				diffuse_b = clamp(diffuse_b, 0.0, 1.0);

				specular_r = clamp(specular_r, 0.0, 1.0);
				specular_g = clamp(specular_g, 0.0, 1.0);
				specular_b = clamp(specular_b, 0.0, 1.0);

				ka = clamp(ka, 0.0, 1.0); 
				kd = clamp(kd, 0.0, 1.0); 
				ks = clamp(ks, 0.0, 1.0); 

				RGB diffuseColor = RGB(diffuse_r, diffuse_g, diffuse_b);
				RGB specularColor = RGB(specular_r, specular_g, specular_b);

				Material *m = new Material();
				m->setDiffuseColor(diffuseColor); 
				m->setSpecularColor(specularColor); 
				m->setAmbientConstant(ka); 
				m->setDiffuseConstant(kd); 
				m->setSpecularConstant(ks); 
				m->setShininess(n); 
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

			else if (variable == "ellipsoid") {
				double cx, cy, cz, rx, ry, rz;
				ss >> cx >> cy >> cz >> rx >> ry >> rz;
				// Check if a material exists
				if (material) {
					Ellipsoid *e = new Ellipsoid(Point3(cx, cy, cz), rx, ry, rz);
					e->setMaterial(*material);
					objects.push_back(e);
				} else {
					std::cerr << "Error: No material was specified before defining a ellipsoid." << std::endl;
					exit(EXIT_FAILURE);
				}
			}

			else if (variable == "v") {
				double x, y, z; 
				ss >> x >> y >> z; 
				Point3 p = Point3(x, y, z); 
				vertices.push_back(p); 
			}

			else if (variable == "f") {
				int v1, v2, v3; 
				ss >> v1 >> v2 >> v3; 
				// Check if a material exists
				if (material) {
					Triangle *t = new Triangle(&vertices, v1, v2, v3, 0, 0, 0); 
					t->setMaterial(*material); 
					objects.push_back(t); 
				} else {
					std::cerr << "Error: No material was specified before defining a triangle." << std::endl;
					exit(EXIT_FAILURE);
				}
			}

			else if (variable == "light") {
				double x, y, z, w; 
				double r, g, b; 
				ss >> x >> y >> z >> w; 
				ss >> r >> g >> b; 

				// check if w is invalid
				if (w != 1 && w != 0) {
					std::cerr << "Error: Invalid input for light. 'w' must be 0 or 1." << std::endl;
					exit(EXIT_FAILURE);
				}

				r = clamp(r, 0.0, 1.0);
				g = clamp(g, 0.0, 1.0);
				b = clamp(b, 0.0, 1.0);

				HVector position = HVector(x, y, z, w); 
				RGB color = RGB(r, g, b); 
				Light l = Light(position, color); 
				lights.push_back(l); 

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
	if (width == 0 || height == 0) {
		std::cerr << "Error: Invalid image width or height." << std::endl;
		exit(EXIT_FAILURE);
	}
	Image img = Image(width, height);

	// Create perspective camera
	double aspectRatio = (double)(width) / height;
	Perspective camera = Perspective(cameraPosition, viewingDirection, upDirection, width, height, verticalFieldOfView);

	// Map pixel to 3D viewing window and trace a ray
	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
			Ray ray = camera.getRay(column, row); 
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

RGB Kernel::ShadeRay(Point3 &point, Surface *object) {

	RGB finalColor = RGB(0, 0, 0); 
	Material material = object->getMaterial();

	// Find normal of object at point 
	Vector3 normal = object->getNormalForPoint(point);
	normal = normal.normalize(); 

	// For each light determine the diffuse and specular color
	for (int index = 0; index < lights.size(); index++) {
		Light light = lights.at(index);  
		HVector lightPosition = light.getPosition(); 
		Vector3 lightSourceDirection;
		// Directional light source
		if (lightPosition.w == 0) { 
			lightSourceDirection = (-1.0) * Vector3(lightPosition.x, lightPosition.y, lightPosition.z); 
		}
		// Positional light source
		else {
			lightSourceDirection = Point3(lightPosition.x, lightPosition.y, lightPosition.z) - point; 
		}

		// Normalize light source direction
		lightSourceDirection = lightSourceDirection.normalize(); 

		RGB tempColor = RGB(0, 0, 0); 
		double shadowFlag; 

		// Determine if objects obscure the light source 

		Ray r = Ray(point, lightSourceDirection); 
		shadowFlag = findShadow(r, light); 

		// Diffuse component
		RGB diffuseComponent = material.getDiffuseConstant() * material.getDiffuseColor() * fmax(0, (normal.dot(lightSourceDirection)));
		tempColor = tempColor + diffuseComponent; 

		// Specular component 
		Vector3 viewerDirection = cameraPosition - point; 
		viewerDirection = viewerDirection.normalize(); 

		Vector3 halfwayVector = lightSourceDirection + viewerDirection.normalize(); 
		halfwayVector = halfwayVector.normalize(); 

		RGB specularComponent = material.getSpecularConstant() * material.getSpecularColor() * pow(fmax(0, (normal.dot(halfwayVector))), material.getShininess());
		tempColor = tempColor + specularComponent; 

		// Draw shadows 
		tempColor = shadowFlag * tempColor; 

		finalColor = finalColor + (light.getColor() * tempColor); 
	}

	// Ambient component
	RGB ambientComponent = material.getAmbientConstant() * material.getDiffuseColor();
	finalColor = finalColor + ambientComponent;  

	// Clamp color 
	finalColor.r = clamp(finalColor.r, 0.0, 1.0);
	finalColor.g = clamp(finalColor.g, 0.0, 1.0);
	finalColor.b = clamp(finalColor.b, 0.0, 1.0);
	
	return finalColor; 
}

double Kernel::findShadow(Ray &ray, Light &light) {

	double lightType = (light.getPosition()).w;
	bool softShadows = false; 

	// Render soft shadows
	if (softShadows && (lightType == POSITIONAL_LIGHT_SOURCE_TYPE)) {
		// Random number distribution
		std::uniform_real_distribution<double> dist(-2.0, 2.0);  //(min, max)
	    //Mersenne Twister
	    std::mt19937 rng; 
	    //Initialize with non-deterministic seeds
	    rng.seed(std::random_device{}()); 

	    double numberOfShadowHits = 0; 
		double numberOfJitterSamples = 80; 
		for (int jitterCount = 0; jitterCount < numberOfJitterSamples; jitterCount++) {
			double jitterFactorX = dist(rng); 
			double jitterFactorY = dist(rng); 
			double jitterFactorZ = dist(rng); 

			// Original light position 
			HVector lightPosition = light.getPosition(); 
			// Jitter the light's position
			Point3 jitteredLightPosition = Point3(jitterFactorX + lightPosition.x, jitterFactorY + lightPosition.y, jitterFactorZ + lightPosition.z);
			// Create jittered ray 
			Vector3 jitteredVector = Vector3(jitteredLightPosition.x, jitteredLightPosition.y, jitteredLightPosition.z); 
			jitteredVector = jitteredVector.normalize(); 
			Ray jitteredRay = Ray(ray.origin, jitteredVector);
			// Create jittered light
			Light jitteredLight = Light(HVector(jitteredLightPosition.x, jitteredLightPosition.y, jitteredLightPosition.z, lightPosition.w), light.getColor()); 

			numberOfShadowHits += isInShadow(jitteredRay, objects, jitteredLight); 
		}
		return (numberOfShadowHits / numberOfJitterSamples); 
	} 
	// Render without soft shadows
	else {
		return isInShadow(ray, objects, light); 
	}
}

double Kernel::isInShadow(Ray &ray, std::vector<Surface*> &objects, Light &light) {
	HVector lightPosition = light.getPosition(); 
	double lightT = (Point3(lightPosition.x, lightPosition.y, lightPosition.z) - ray.origin).magnitude();

	// For each object, check if a shadow ray hits it
	Surface *object;
	for (int index = 0; index < objects.size(); index++) {
		Surface *testObject = objects.at(index);
		double tempMinT = testObject->hit(ray);

		// Directional light source
		if (lightPosition.w == 0) {
			// A shadow exists
			if (tempMinT > SHADOW_RAY_INTERSECTION_THRESHOLD) {
				return 0.0; 
			}
		}
		// Positional light source
		else if (lightPosition.w == 1) {
			if (tempMinT > SHADOW_RAY_INTERSECTION_THRESHOLD && tempMinT < lightT) {
				return 0.0; 
			}
		}
	}

	// No objects obscure the light source
	return 1.0; 
}




