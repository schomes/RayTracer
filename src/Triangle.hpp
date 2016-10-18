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
	// Pointer to a texture coordinate array
	std::vector<Vector3> *textureArray; 
	// Pointer to a per-vertex normal array 
	std::vector<Vector3> *normalArray; 
	// Indices into the vertex array 
	int p0, p1, p2; 
	// Indices into the texture coordinate array
	int t0, t1, t2; 
	// Indices into the normal array 
	int n0, n1, n2; 

public: 
	Triangle() {}
	Triangle(std::vector<Point3> *vertexArray_in, std::vector<Vector3> *textureArray_in, std::vector<Vector3> *normalArray_in, int p0_in, int p1_in, int p2_in, int t0_in, int t1_in, int t2_in, int n0_in, int n1_in, int n2_in) : vertexArray(vertexArray_in), textureArray(textureArray_in), normalArray(normalArray_in), p0(p0_in), p1(p1_in), p2(p2_in), t0(t0_in), t1(t1_in), t2(t2_in), n0(n0_in), n1(n1_in), n2(n2_in) {}

	double hit(Ray &ray); 
	Vector3 getNormalForPoint(Point3 &point); 
	RGB getTextureColor(Point3 &p); 
}; 

#endif