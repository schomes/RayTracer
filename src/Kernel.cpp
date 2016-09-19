#include "Kernel.hpp"
#include <iostream> 

void Kernel::readScene(std::ifstream &inputFile) {
	if (inputFile.is_open()) {
		std::string line = ""; 
		while(std::getline(inputFile, line)) {
			std::cout << line << std::endl; 
		}
	}
}