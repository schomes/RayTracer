#include "Image.hpp"
#include <iostream>
#include <fstream> 

Image::Image(int width_in, int height_in) : width(width_in), height(height_in) {
	// Set all pixels to black
	RGB defaultColor = RGB(0, 0, 0); 
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			image.push_back(defaultColor); 
		}
	}
}

void Image::setPixel(const RGB &pixel, int x, int y) {
	// Determine the 1D coordinate from 2D coordinate (x, y). 
	int index = x + width * y; 
	// Set the color of the pixel. 
	image.at(index) = pixel; 
}

void Image::saveImageAsPPM(const std::string filePath) {
	using std::cout; 
	using std::endl; 
	using std::ofstream; 

	cout << "Saving " << width << " by " << height << " image to file " << filePath << endl; 

	ofstream file (filePath); 
	if (file.is_open()) {

		// Write image header
		//... Image format 
		file << "P3" << endl; 
		//... Number of columns and rows 
		file << width << " " << height << endl; 
		//... Maximum color value  
		file << maximumColorValue << endl; 

		// Write image data 
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				// Determine the 1D coordinate from 2D coordinate (x, y). 
				int index = x + width * y; 
				RGB p = image.at(index); 
				// Save the color; add spaces to provide clarity if the file is read by a human.
				file << p.r << " "; 
				file << p.g << " "; 
				file << p.b << "  "; 
			}
			file << endl; 
		}

		file.close(); 

	} 

}