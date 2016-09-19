#include <iostream>
#include "Image.hpp"

int main( int argc, char **argv ){

	Image img = Image(50, 50, RGB(125, 55, 186)); 
	img.saveImageAsPPM("img.ppm"); 

	return 0; 
}