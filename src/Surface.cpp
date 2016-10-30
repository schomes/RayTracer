#include "Surface.hpp"
#include <cmath>

#include <iostream> 

double Surface::getFresnelReflectance(Ray &incidentRay, double incomingIndexOfRefraction, double transmittedIndexOfRefraction) {

	//double indexOfRefraction = material.getIndexOfRefraction(); 
	// Reflection coefficient for the angle of incidence of the incoming ray; controls the sensitivity of the surface reflectivity 
	double reflectionCoefficient = pow(((transmittedIndexOfRefraction - incomingIndexOfRefraction) / (transmittedIndexOfRefraction + incomingIndexOfRefraction)), 2); 

	Point3 point = incidentRay.origin + incidentRay.direction; 
	Vector3 normal = getNormalForPoint(point);
	normal = normal.normalize(); 

	Vector3 incidentRayVector = -1 * incidentRay.direction; 
	incidentRayVector = incidentRayVector.normalize(); 

	double incidentNormalAngle = incidentRayVector.dot(normal);

	double fresnelReflectance = reflectionCoefficient + (1 - reflectionCoefficient) * pow((1 - incidentNormalAngle), 5); 

	/*
	std::cout << "indexOfRefraction: " << indexOfRefraction << std::endl; 
	std::cout << "reflectionCoefficient: " << reflectionCoefficient << std::endl; 
	std::cout << "point: " << point.x << " " << point.y << " " << point.z << std::endl; 
	std::cout << "incident ray: " << (incidentRay.direction).x << " " << (incidentRay.direction).y << " " << (incidentRay.direction).z << std::endl; 
	std::cout << "normal: " << normal.x << " " << normal.y << " " << normal.z << std::endl;
	std::cout << "incidentNormalAngle: " << incidentNormalAngle << std::endl; 
	std::cout << "Fresnel: " << fresnelReflectance << std::endl; 
	*/ 

	return fresnelReflectance; 
}


Ray Surface::getTransmittedRayDirection(Ray &incidentRay, double incomingIndexOfRefraction, double transmittedIndexOfRefraction) {

	Point3 intersectionPoint = incidentRay.origin; 

	// Find normal for point
	//Vector3 normal = getNormalForPoint(intersectionPoint); 
	// normal = normal.normalize(); 
	Vector3 normal = Vector3(0, 1.0, 0); 

	Vector3 incidentRayDirection = (incidentRay.direction).normalize(); 

	// Calculate cos() N.dot(incidentRayDirection)
	//double cosineOfIncidentAngle = normal.dot(incidentRayDirection); 
	double cosineOfIncidentAngle = normal.dot(incidentRayDirection); 

	//std::cout << "cosineOfIncidentAngle: " << cosineOfIncidentAngle << std::endl; 

	//std::cout << "sin2i: " << (1.0 - pow(cosineOfIncidentAngle, 2.0)) << std::endl; 

	//std::cout << "cosT: " << sqrt(1 - (pow((incomingIndexOfRefraction / transmittedIndexOfRefraction), 2.0) * (1 - pow(cosineOfIncidentAngle, 2.0)))) << std::endl; 

	Vector3 transmittedRayDirection = (-1 * normal) 
							        * sqrt(1 - (pow((incomingIndexOfRefraction / transmittedIndexOfRefraction), 2.0) * (1 - pow(cosineOfIncidentAngle, 2.0)))) 
							        + (incomingIndexOfRefraction / transmittedIndexOfRefraction) * (cosineOfIncidentAngle * normal - incidentRayDirection); 

	return Ray(intersectionPoint, transmittedRayDirection); 

}