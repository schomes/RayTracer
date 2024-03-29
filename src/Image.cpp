#include "Image.hpp"
#include <iostream>
#include <fstream>
#include <sstream> /* string streams */

Image::Image(int width_in, int height_in) : width(width_in), height(height_in) {
	// Set all pixels to black
	RGB defaultColor = RGB(0, 0, 0);
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			image.push_back(defaultColor);
		}
	}
}

// Reads (imports) image 
Image::Image(const std::string filePath) {
	std::ifstream inputFile(filePath.c_str());
	if (inputFile.is_open()) {
		std::string line = "";

		// get headers 
		if (std::getline(inputFile, line)) {
			std::stringstream ss(line);
			std::string p3; 
			int w, h; 
			ss >> p3 >> w >> h; 
			width = w; 
			height = h; 
		}

		while(std::getline(inputFile, line)) {
			std::stringstream ss(line);
			int r = 0; 
			int g = 0; 
			int b = 0; 
			while (ss >> r) {
				// set pixel
				ss >> g >> b; 
				RGB pixel = RGB(r, g, b); 
				image.push_back(pixel); 
			}
		}
	}
}

void Image::setPixel(const RGB &pixel, int x, int y) {
	// Determine the 1D coordinate from 2D coordinate (x, y).
	int index = x + width * y;
	// convert colors in range 0 - 1 to range 0 - 255
	RGB p = RGB((int)(maximumColorValue * pixel.r), (int)(maximumColorValue * pixel.g), (int)(maximumColorValue * pixel.b));
	// Set the color of the pixel.
	image.at(index) = p;
}

RGB Image::getPixel(int x, int y) {
	// Determine the 1D coordinate from 2D coordinate (x, y).
	int index = x + width * y;
	return image.at(index); 
}

void Image::saveImageAsPPM(const std::string filePath) {
	using std::cout;
	using std::endl;
	using std::ofstream;

	cout << "Saving " << width << " by " << height << " image to file " << filePath << endl;

	ofstream file (filePath.c_str()); 
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
