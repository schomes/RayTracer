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

	// render scene 
	Image img = raytracer.render(); 

	//save image
	img.saveImageAsPPM("img.ppm"); 




	// Initialize raytracer (calculate coordinate-frame for camera, setup viewing plane)

	// raytracer.TraceRays(); 

	/*
	std::cout << raytracer.cameraPosition.x << std::endl; 
	std::cout << raytracer.cameraPosition.y << std::endl; 
	std::cout << raytracer.cameraPosition.z << std::endl; 

	std::cout << raytracer.viewingDirection.x << std::endl; 
	std::cout << raytracer.viewingDirection.y << std::endl; 
	std::cout << raytracer.viewingDirection.z << std::endl; 

	std::cout << raytracer.upDirection.x << std::endl; 
	std::cout << raytracer.upDirection.y << std::endl; 
	std::cout << raytracer.upDirection.z << std::endl; 

	std::cout << raytracer.verticalFieldOfView << std::endl; 

	std::cout << raytracer.width << std::endl; 
	std::cout << raytracer.height << std::endl; 

	std::cout << raytracer.bkgcolor.r << std::endl; 
	std::cout << raytracer.bkgcolor.g << std::endl; 
	std::cout << raytracer.bkgcolor.b << std::endl; 

	std::cout << raytracer.materialColor.r << std::endl; 
	std::cout << raytracer.materialColor.g << std::endl; 
	std::cout << raytracer.materialColor.b << std::endl;
	*/ 

	return 0; 
}