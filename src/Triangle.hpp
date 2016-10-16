#ifndef TRIANGLE_H 
#define TRIANGLE_H

#include <vector>
#include "Surface.hpp"
#include "Point3.hpp"
#include "Vector3.hpp"
#include "Ray.hpp"
#include "Material.hpp"

class Triangle : public Surface {
private: 
	// Pointer to a vertex array 
	std::vector<Point3> *vertexArray; 
	// Indices into the vertex array 
	int p0, p1, p2; 
	// Indices into the normal array 
	int n0, n1, n2; 

public: 
	Triangle() {}
	Triangle(std::vector<Point3> *vertexArray_in, int p0_in, int p1_in, int p2_in, int n0_in, int n1_in, int n2_in) : vertexArray(vertexArray_in), p0(p0_in), p1(p1_in), p2(p2_in), n0(n0_in), n1(n1_in), n2(n2_in) {}

	double hit(Ray &ray); 
	Vector3 getNormalForPoint(Point3 &point); 
}; 

#endif