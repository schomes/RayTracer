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
#include "Orthographic.hpp"

#define MAX_COLOR_VALUE 255 // maximum value for an RGB component
#define FAR_CLIP 1000.0 // maximum distance to consider ray collision
#define INTERSECTION_THRESHOLD 0.001 // Used to reject spurious self-intersections when detecting shadows
#define POSITIONAL_LIGHT_SOURCE_TYPE 1 // Positional light source
#define AIR_INDEX_OF_REFRACTION 1

/// These are debugging statements

bool inObject = false; 

//////////////////////////////////

double clamp(double number, double min, double max) {
	return std::max(min, std::min(number, max));
}

void parseToken(std::string token, int *vertex, int *vertexTexture, int *vertexNormal) {
	// Get value of index into vertex array  
	int pos = 0; 
	// ... if the token is only a vertex index
	if ((pos = token.find("/")) == std::string::npos) {
		*vertex = std::stoi(token); 
		return; 
	} 
	// ... If the token contains slashes
	else {
		*vertex = std::stoi(token.substr(0, pos)); 
	}

	// Get value of index into texture coordinate array
	int startPos = pos + 1; 
	// ... If the token contains only vertex and texture indices 
	if ((pos = token.find("/", startPos)) == std::string::npos) {
		*vertexTexture = std::stoi(token.substr(startPos, pos)); 
		return; 
	}
	// ... If there is texture coordinate index
	else if (startPos != pos) {
		*vertexTexture = std::stoi(token.substr(startPos, pos-2)); 
	}

	// Get value of index into normal array 
	startPos = pos+1; 
	if ((pos = token.find("/", startPos)) == std::string::npos) {
		*vertexNormal = std::stoi(token.substr(startPos, pos)); 
	}
	else {
		// ERROR 
	}
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

			else if (variable == "parallel") {
				cameraType = ORTHOGRAPHIC_TYPE; 
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

				double opacity, indexOfRefraction; 

				ss >> diffuse_r >> diffuse_g >> diffuse_b; 
				ss >> specular_r >> specular_g >> specular_b; 
				ss >> ka >> kd >> ks; 
				ss >> n; 
				ss >> opacity >> indexOfRefraction; 

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
				m->setOpacity(opacity); 
				m->setIndexOfRefraction(indexOfRefraction); 
				material = m;

			}

			// Texture
			else if (variable == "texture") {
				// import (read) texture image 
				// add texture image to vector
				std::string fileName = ""; 
				ss >> fileName; 
				Image texture = Image(fileName);  
				textures.push_back(texture); 
			}

			else if (variable == "sphere") {
				double x, y, z, r;
				ss >> x >> y >> z >> r;
				// Check if a material exists
				Sphere *s; 
				if (material) {
					s = new Sphere(Point3(x, y, z), r);
					s->setMaterial(*material);
					objects.push_back(s);
				} else {
					std::cerr << "Error: No material was specified before defining a sphere." << std::endl;
					exit(EXIT_FAILURE);
				}

				// Check if texture exists
				if (!textures.empty()) {
					s->setTexture(&textures.back()); 
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

			// Vertices
			else if (variable == "v") {
				double x, y, z; 
				ss >> x >> y >> z;
				Point3 p = Point3(x, y, z); 
				vertices.push_back(p); 
			}

			// Per-vertex surface normals
			else if (variable == "vn") {
				double x, y, z; 
				ss >> x >> y >> z; 
				Vector3 surfaceNormal = Vector3(x, y, z); 
				perVertexSurfaceNormals.push_back(surfaceNormal); 
			}

			// Texture coordinates 
			else if (variable == "vt") {
				double x, y; 
				ss >> x >> y; 
				Vector3 textureCoordinate = Vector3(x, y, 0); 
				textureCoordinates.push_back(textureCoordinate); 
			}

			// Triangles (faces)
			else if (variable == "f") {
				int v1, v2, v3; // Indices into the vertex array
				// Indices into the texture coordinate array
				int t1 = 0; 
				int t2 = 0; 
				int t3 = 0; 
				// Indices into the normal array 
				int n1 = 0;
				int n2 = 0;
				int n3 = 0;

				std::string token = ""; 

				// First vertex
				ss >> token; 
				parseToken(token, &v1, &t1, &n1); 

				// Second vertex
				ss >> token; 
				parseToken(token, &v2, &t2, &n2); 

				// Third vertex
				ss >> token; 
				parseToken(token, &v3, &t3, &n3); 

				Triangle *t; 
				// Check if a material exists
				if (material) {
					t = new Triangle(&vertices, &textureCoordinates, &perVertexSurfaceNormals, v1, v2, v3, t1, t2, t3, n1, n2, n3); 
					t->setMaterial(*material); 
					objects.push_back(t); 
				} else {
					std::cerr << "Error: No material was specified before defining a triangle." << std::endl;
					exit(EXIT_FAILURE);
				}

				// Check if texture exists
				if (!textures.empty()) {
					t->setTexture(&(textures.back())); 
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

			else if (variable == "viewdist") {
				double d; 
				ss >> d; 
				distance = d; 
			}

			// Empty line 
			else if (variable.find_first_not_of (' ') == variable.npos) {
				continue;
			}

			else if (variable == "#" || variable == "o" || variable == "mtllib" || variable == "usemtl" || variable == "s") {
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

	//std::cout << (perVertexSurfaceNormals.at(0)).x << (perVertexSurfaceNormals.at(0)).y << (perVertexSurfaceNormals.at(0)).z << std::endl; 

	// Initialize output image
	if (width == 0 || height == 0) {
		std::cerr << "Error: Invalid image width or height." << std::endl;
		exit(EXIT_FAILURE);
	}
	Image img = Image(width, height);

	// Create perspective camera
	double aspectRatio = (double)(width) / height;

	Camera *camera; 

	if (cameraType == ORTHOGRAPHIC_TYPE) {
		// If depth of field is activated 
		if (distance > NO_DEPTH_OF_FIELD_TAG) {
			camera = new Orthographic(cameraPosition, viewingDirection, upDirection, width, height, verticalFieldOfView, distance);
		} else {
			camera = new Orthographic(cameraPosition, viewingDirection, upDirection, width, height, verticalFieldOfView);
		}
		
	} else {
		// If depth of field is activated
		if (distance > NO_DEPTH_OF_FIELD_TAG) {
			camera = new Perspective(cameraPosition, viewingDirection, upDirection, width, height, verticalFieldOfView, distance);
		} else {
			camera = new Perspective(cameraPosition, viewingDirection, upDirection, width, height, verticalFieldOfView);
		}
	} 

	// Map pixel to 3D viewing window and trace a ray
	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {

			RGB color = RGB(0, 0, 0); 
			if (distance > NO_DEPTH_OF_FIELD_TAG) {
				int numberOfJitters = 100; 
				std::vector<Ray> rayCluster = camera->getRayCluster(column, row, numberOfJitters); 
				for (int rayClusterIndex = 0; rayClusterIndex < rayCluster.size(); rayClusterIndex++) {
					Ray ray = rayCluster.at(rayClusterIndex); 
					RGB tempColor = TraceRay(ray, 0);
					color = color + tempColor; 
				}

				color = color * (1.0 / numberOfJitters); 

			} else {
				Ray ray = camera->getRay(column, row);
				color = TraceRay(ray, 0);	
			}

			// Clamp color 
			color.r = clamp(color.r, 0.0, 1.0);
			color.g = clamp(color.g, 0.0, 1.0);
			color.b = clamp(color.b, 0.0, 1.0);

			img.setPixel(color, column, row);

			// Print progress to terminal
			std::cout << "\rProgress: " << (int)((double(column + width * row) / (width * height)) * 100.0) << "%";

		}
	}
	return img;
}

RGB Kernel::TraceRay(Ray &ray, int depth) {

	if (depth > 4) {
		return RGB(0, 0, 0); 
	}

	RGB color = bkgcolor;

	// For each object in the scene, check for intersection with ray
	Surface *object;
	double minT = FAR_CLIP;
	// for each object, check if a ray hits it
	for (int index = 0; index < objects.size(); index++) {
		Surface *testObject = objects.at(index);
		double tempMinT = testObject->hit(ray);

		if ((tempMinT > INTERSECTION_THRESHOLD) && (tempMinT < minT)) {
			object = testObject;
			minT = tempMinT;
		}
	}

	// We didn't hit anything in front of us, so return background color
	if (minT == FAR_CLIP) {
		return color;
	} else {
		//Point3 shadingCoordinate = ray.origin + (minT * ray.direction);
		Point3 incidentRayOrigin = ray.origin; 
		Vector3 incidentRayDirection = minT * ray.direction;
		Ray incidentRay = Ray(incidentRayOrigin, incidentRayDirection);
		return ShadeRay(incidentRay, object, depth);
	}
}

RGB Kernel::ShadeRay(Ray &ray, Surface *object, int depth) {

	// Shading coordinate
	Point3 point = ray.origin + ray.direction; 

	RGB finalColor = RGB(0, 0, 0); 
	Material material = object->getMaterial();

	// Find normal of object at point 
	Vector3 normal = object->getNormalForPoint(point);
	normal = normal.normalize(); 

	// Reverse the direction of the incoming ray
	Vector3 incomingRayDirectionReversed = (-1 * (ray.direction)).normalize();  
	double angleOfIncidenceCosine = normal.dot(incomingRayDirectionReversed);

	// Determine indices of refraction depending on if the ray is going into or out of an object 
	// This implementation assumes that there are no intersecting surfaces or full containment of a surface in another
	double objectIndexOfRefraction = (object->getMaterial()).getIndexOfRefraction();  
	double incomingIndexOfRefraction; 
	double transmittedIndexOfRefraction;   

	// Ray hits the outside of a surface 
	if (angleOfIncidenceCosine > 0) { 
		incomingIndexOfRefraction = AIR_INDEX_OF_REFRACTION; 
		transmittedIndexOfRefraction = objectIndexOfRefraction;  
	}
	// Ray hits the inside of a surface  
	else {
		incomingIndexOfRefraction = objectIndexOfRefraction; 
		transmittedIndexOfRefraction = AIR_INDEX_OF_REFRACTION; 
		// Flip the normal because we are inside of a surface
		normal = -1 * normal; 
		normal = normal.normalize(); 
		angleOfIncidenceCosine = normal.dot(incomingRayDirectionReversed);
	}

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
		RGB diffuseComponent = material.getDiffuseConstant() * object->getTextureColor(point) * fmax(0, (normal.dot(lightSourceDirection)));
		tempColor = tempColor + diffuseComponent; 

		// Specular component 
		Vector3 viewerDirection = ray.origin - point; 
		viewerDirection = viewerDirection.normalize(); 

		Vector3 halfwayVector = lightSourceDirection + viewerDirection.normalize(); 
		halfwayVector = halfwayVector.normalize(); 

		RGB specularComponent = material.getSpecularConstant() * material.getSpecularColor() * pow(fmax(0, (normal.dot(halfwayVector))), material.getShininess());
		tempColor = tempColor + specularComponent; 

		// Draw shadows 
		tempColor = shadowFlag * tempColor; 

		// Add light's color
		finalColor = finalColor + (light.getColor() * tempColor); 
	}


	// Ambient component
	RGB ambientComponent = material.getAmbientConstant() * object->getTextureColor(point);
	finalColor = finalColor + ambientComponent;  


	// Specular reflection component 

	// Find Fresnel Reflectance 
	double fresnelReflectance = object->getFresnelReflectance(ray, normal, incomingIndexOfRefraction, transmittedIndexOfRefraction); 

	// Find illumination given by a reflection ray 
	Vector3 reflectedRayDirection = (2 * angleOfIncidenceCosine * normal) - incomingRayDirectionReversed; 
	Ray reflectedRay = Ray(point, reflectedRayDirection); 

	RGB specularReflectionColor = fresnelReflectance * TraceRay(reflectedRay, depth+1);
	finalColor = finalColor + specularReflectionColor; 


	// Transparent component 

	// Check for Total Internal Reflection 
	double angleOfIncidenceSin = sqrt(1 - pow(angleOfIncidenceCosine, 2.0)); 
	if (!(angleOfIncidenceSin > (transmittedIndexOfRefraction / incomingIndexOfRefraction))) {
		Ray incidentRay = Ray(point, incomingRayDirectionReversed); 
		Ray transmittedRay = object->getTransmittedRayDirection(incidentRay, normal, incomingIndexOfRefraction, transmittedIndexOfRefraction); 

		RGB transparentColor = (1.0 - fresnelReflectance) * (1.0 - material.getOpacity()) * TraceRay(transmittedRay, depth+1); 
		finalColor = finalColor + transparentColor; 	
	}

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
	ray.origin = ray.origin + (0.001 * (ray.direction).normalize()); 
	HVector lightPosition = light.getPosition(); 
	double lightT = (Point3(lightPosition.x, lightPosition.y, lightPosition.z) - ray.origin).magnitude();

	double shadowFactor = 1.0; // Default to no objects obscuring the light source 

	// For each object, check if a shadow ray hits it
	Surface *object;
	for (int index = 0; index < objects.size(); index++) {
		Surface *testObject = objects.at(index);
		double tempMinT = testObject->hit(ray);

		// Directional light source
		if (lightPosition.w == 0) {
			// A shadow exists
			if (tempMinT > INTERSECTION_THRESHOLD) {
				shadowFactor -= (testObject->getMaterial()).getOpacity(); 
			}
		}
		// Positional light source
		else if (lightPosition.w == 1) {
			if (tempMinT > INTERSECTION_THRESHOLD && tempMinT < lightT) {
				shadowFactor -= (testObject->getMaterial()).getOpacity();  
			}
		}
	}

	// No objects obscure the light source
	return fmax(0.0, shadowFactor); 
}




