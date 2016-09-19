#include <iostream>
#include <fstream> 
#include "Kernel.hpp"
#include "Image.hpp"

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


	Image img = Image(50, 50, RGB(125, 55, 186)); 
	img.saveImageAsPPM("img.ppm"); 

	return 0; 
}