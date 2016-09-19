#ifndef RGB_H
#define RGB_H

// This structure represents a color with red, green, and blue components. 
struct RGB {
	int r;
	int g; 
	int b; 
	RGB(int r = 0, int g = 0, int b = 0) : r(r), g(g), b(b) {}
}; 

#endif 