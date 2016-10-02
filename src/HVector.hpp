#ifndef H_VECTOR_H 
#define H_VECTOR_H

// 
class HVector {
public: 
	double x;  
	double y; 
	double z; 
	double w; 

	HVector(double x_in, double y_in, double z_in, double w_in) : x(x_in), y(y_in), z(z_in), w(w_in) {}
};

#endif