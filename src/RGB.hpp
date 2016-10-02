#ifndef RGB_H
#define RGB_H

// This structure represents a color with red, green, and blue components. 
// Each component is represented by values between 0.0 and 1.0 inclusive.
struct RGB {
	double r;
	double g; 
	double b; 
	RGB(double r = 0, double g = 0, double b = 0) : r(r), g(g), b(b) {}
}; 

#endif 