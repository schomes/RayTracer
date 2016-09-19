#ifndef POINT3_H
#define POINT3_H

class Point3 {
public: 
	double x; 
	double y; 
	double z; 

	Point3(double x_in = 0, double y_in = 0, double z_in = 0) : x(x_in), y(y_in), z(z_in) {}
}; 

#endif