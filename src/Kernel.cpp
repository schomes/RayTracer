#include "Kernel.hpp"
#include <iostream> 
#include <sstream> // string streams 

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

			}

			else if (variable == "updir") {
				
			}





		}
	}
}