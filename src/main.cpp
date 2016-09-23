#include <iostream>
#include <fstream> 
#include "Kernel.hpp"
#include "Image.hpp"

// testing
#include "Vector3.hpp"

int main( int argc, char **argv ) {

	// check if input file has been specified 
	if (argc < 2) {
		std::cerr << "**Error: an input file must be specified." << std::endl; 
		return 0; 
	}

	// Initialize kernel and read scene description 
	Kernel raytracer; 
	std::string filename(argv[1]); 
	std::ifstream inputFile(filename.c_str()); 
	raytracer.readScene(inputFile); 

	// render scene 
	Image img = raytracer.render(); 

	//save image
	img.saveImageAsPPM("img.ppm"); 

	return 0; 
}