#include <iostream>
#include <fstream>
#include "RayTracer.hpp"
#include "Image.hpp"

// testing
#include "Vector3.hpp"

int main( int argc, char **argv ) {

	// Check if input file has been specified
	if (argc < 2) {
		std::cerr << "**Error: an input file must be specified." << std::endl;
		return 0;
	}
	
	// Initialize RayTracer and read scene description
	RayTracer raytracer;
	//... Get file name, and save filename without extension
	std::string filename(argv[1]);
	std::size_t indexOfFileExtension = filename.find_last_of(".");
	std::string filenameWithoutExtension = filename.substr(0, indexOfFileExtension);
	//... Read scene description
	std::ifstream inputFile(filename.c_str());
	raytracer.readScene(inputFile);

	// Render scene
	Image img = raytracer.render();

	// Save image
	img.saveImageAsPPM(filenameWithoutExtension + ".ppm");

	return 0;
}
