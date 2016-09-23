#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector> 
#include "RGB.hpp"

// This class represents an image and provides an interface for exporting the image as a PPM file. 
class Image {
private: 
	int width; 
	int height; 
	int maximumColorValue = 255; // Maximum pixel-value allowed
	std::vector<RGB> image; // Holds pixel values to represent an image

public: 
	/*
	 * Constructs an Image. 
	 * \param width The width of the image. 
	 * \param height The height of the image. 
	 * \param backgroundColor The backgroundColor of the image 
	 */
	Image(int width, int height); 

	// Returns the width of the image. 
	int getWidth() const {return width;}

	// Returns the height of the image. 
	int getHeight() const {return height;}

	/*
	 * Sets the color of the pixel at (x, y). 
	 * \param pixel The pixel's new color. 
	 * \param x The x-coordinate of the pixel.
	 * \param y The y-coordinate of the pixel. 
	 */ 
	void setPixel(const RGB &pixel, int x, int y); 

	/*
	 * Saves an image as a PPM file. 
	 * \param filePath The path and name of the new file. 
	 */
	void saveImageAsPPM(const std::string filePath); 

}; // Image

#endif