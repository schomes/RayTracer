#include "Triangle.hpp"

#include <iostream> 

#define NO_COLLISION_FLAG -1.0
#define EPSILON 0.003

double Triangle::hit(Ray &ray) {

	// Ray origin 
	double x0 = (ray.origin).x; 
	double y0 = (ray.origin).y; 
	double z0 = (ray.origin).z; 

	// Ray direction 
	double xd = (ray.direction).x;
	double yd = (ray.direction).y;
	double zd = (ray.direction).z;
	
	// Get vertices from vertex array 
	Point3 v0 = vertexArray->at(p0 - 1); 
	Point3 v1 = vertexArray->at(p1 - 1);
	Point3 v2 = vertexArray->at(p2 - 1);

	// Calculate vectors e1, e2 and n
	Vector3 e1 = v1 - v0; 
	Vector3 e2 = v2 - v0; 
	Vector3 n = e1.cross(e2); 

	// Variables represent components of the plane equation Ax + By + Cz + D = 0
	double A = n.x; 
	double B = n.y; 
	double C = n.z; 
	double D = -(A*(v0.x) + B*(v0.y) + C*(v0.z)); 

	// Calculate the numerator and denominator separately in case the denominator is zero
	double numerator = -((A * x0) + (B * y0) + (C * z0) + D); 
	double denominator = (A * xd) + (B * yd) + (C * zd); 

	if (denominator == 0) {
		return NO_COLLISION_FLAG; 
	}
	else {
		double t = numerator / denominator; 
		Point3 intersectionPoint = ray.origin + (t * ray.direction); 

		Vector3 e3 = intersectionPoint - v1; 
		Vector3 e4 = intersectionPoint - v2; 

		double area = 0.5 * (e1.cross(e2)).magnitude(); 
		double a = 0.5 * (e3.cross(e4)).magnitude(); 
		double b = 0.5 * (e4.cross(e2)).magnitude(); 
		double c = 0.5 * (e1.cross(e3)).magnitude(); 

		double alpha = a / area; 
		double beta = b / area; 
		double gamma = c / area; 

		if ((0 <= alpha) && (alpha <= 1) && (0 <= beta) && (beta <= 1) && (0 <= gamma) && (gamma <= 1) && (alpha + beta + gamma - 1 < EPSILON)) {
			return t; 
		} else {
			return NO_COLLISION_FLAG; 
		}
	}
}

Vector3 Triangle::getNormalForPoint(Point3 &point) {

	// Get vertices from vertex array 
	Point3 v0 = vertexArray->at(p0 - 1); 
	Point3 v1 = vertexArray->at(p1 - 1);
	Point3 v2 = vertexArray->at(p2 - 1);

	// Calculate vectors e1, e2 and n
	Vector3 e1 = v1 - v0; 
	Vector3 e2 = v2 - v0; 

	// Per-vertex surface normals were not included; use flat shading 
	if ((n0 == 0) || (n1 == 0) || (n2 == 0)) {
		Vector3 n = e1.cross(e2); 
		n = n.normalize(); 
		return n; 
	}
	// Use smooth shading 
	else { 

		Vector3 normal0 = normalArray->at(n0 - 1); 
		Vector3 normal1 = normalArray->at(n1 - 1); 
		Vector3 normal2 = normalArray->at(n2 - 1); 

		Vector3 e3 = point - v1; 
		Vector3 e4 = point - v2;

		double area = 0.5 * (e1.cross(e2)).magnitude(); 
		double a = 0.5 * (e3.cross(e4)).magnitude(); 
		double b = 0.5 * (e4.cross(e2)).magnitude(); 
		double c = 0.5 * (e1.cross(e3)).magnitude(); 

		double alpha = a / area; 
		double beta = b / area; 
		double gamma = c / area; 

		Vector3 normal = Vector3((alpha * normal0) + (beta * normal1) + (gamma * normal2)); 
		normal = normal.normalize(); 



		return normal; 

	}

	
}

RGB Triangle::getTextureColor(Point3 &p) {
	if (texture) {

		// Get vertices from vertex array 
		Point3 v0 = vertexArray->at(p0 - 1); 
		Point3 v1 = vertexArray->at(p1 - 1);
		Point3 v2 = vertexArray->at(p2 - 1);

		// Calculate vectors e1, e2 and n
		Vector3 e1 = v1 - v0; 
		Vector3 e2 = v2 - v0; 
		Vector3 e3 = p - v1; 
		Vector3 e4 = p - v2;

		double area = 0.5 * (e1.cross(e2)).magnitude(); 
		double a = 0.5 * (e3.cross(e4)).magnitude(); 
		double b = 0.5 * (e4.cross(e2)).magnitude(); 
		double c = 0.5 * (e1.cross(e3)).magnitude(); 

		double alpha = a / area; 
		double beta = b / area; 
		double gamma = c / area; 

		Vector3 textureCoordinate0 = textureArray->at(t0 - 1); 
		Vector3 textureCoordinate1 = textureArray->at(t1 - 1); 
		Vector3 textureCoordinate2 = textureArray->at(t2 - 1); 

		double u = (alpha * textureCoordinate0.x) + (beta * textureCoordinate1.x) + (gamma * textureCoordinate2.x); 
		double v = (alpha * textureCoordinate0.y) + (beta * textureCoordinate1.y) + (gamma * textureCoordinate2.y); 

		int i = u * (texture->getWidth() - 1); 
		int j = v * (texture->getHeight() - 1); 

		std::cout << i << " " << j << std::endl; 


		return texture->getPixel(i, j); 

		std::cout << "ran" << std::endl; 

		return RGB(1, 0, 0); 
	} else {
		return material.getDiffuseColor();
	}
	 
}


