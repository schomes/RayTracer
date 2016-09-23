#include "Kernel.hpp"
#include <iostream> 
#include <sstream> // string streams
#include "Point3.hpp"
#include "RGB.hpp" 
#include "Sphere.hpp"

#define MAX_COLOR_VALUE 255

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
				Material m = Material(); 
				m.setMaterialColor(materialColor); 
				material = m; 
			}

			else if (variable == "sphere") {
				double x, y, z, r; 
				ss >> x >> y >> z >> r; 
				Sphere s = Sphere(Point3(x, y, z), r); 
				objects.push_back(s); 
			}


		}
	}
}