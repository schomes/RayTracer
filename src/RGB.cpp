#include "RGB.hpp"

RGB RGB::operator + (const RGB & rhs) const {
	return RGB(r + rhs.r, g + rhs.g, b + rhs.b); 
}