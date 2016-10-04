#ifndef RGB_H
#define RGB_H

// This structure represents a color with red, green, and blue components. 
// Each component is represented by values between 0.0 and 1.0 inclusive.
class RGB {
public: 
	double r;
	double g; 
	double b; 
	RGB(double r = 0, double g = 0, double b = 0) : r(r), g(g), b(b) {}

	RGB operator + (const RGB &) const; 
	RGB operator * (const RGB &) const; 
}; 

// scalar, RGB multiplication: s * RGB
inline RGB operator * (double lhs, RGB rhs) {
	return RGB(lhs * rhs.r, lhs * rhs.g, lhs * rhs.b); 
}

// scalar, RGB multiplication: RGB * s
inline RGB operator * (RGB lhs, double rhs) {
	return RGB(lhs.r * rhs, lhs.g * rhs, lhs.b * rhs); 
}

#endif 