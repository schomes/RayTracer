#include "Surface.hpp"
#include <cmath>

#include <iostream> 

double Surface::getFresnelReflectance(Ray &incidentRay, Vector3 normal, double incomingIndexOfRefraction, double transmittedIndexOfRefraction) {

	//double indexOfRefraction = material.getIndexOfRefraction(); 
	// Reflection coefficient for the angle of incidence of the incoming ray; controls the sensitivity of the surface reflectivity 
	double reflectionCoefficient = pow(((transmittedIndexOfRefraction - incomingIndexOfRefraction) / (transmittedIndexOfRefraction + incomingIndexOfRefraction)), 2); 

	Point3 point = incidentRay.origin + incidentRay.direction; 
	//Vector3 normal = getNormalForPoint(point);
	normal = normal.normalize(); 

	Vector3 incidentRayVector = -1 * incidentRay.direction; 
	incidentRayVector = incidentRayVector.normalize(); 

	double incidentNormalAngle = incidentRayVector.dot(normal);

	double fresnelReflectance = reflectionCoefficient + (1 - reflectionCoefficient) * pow((1 - incidentNormalAngle), 5); 

	return fresnelReflectance; 
}


Ray Surface::getTransmittedRayDirection(Ray &incidentRay, Vector3 normal, double incomingIndexOfRefraction, double transmittedIndexOfRefraction) {

	Point3 intersectionPoint = incidentRay.origin; 

	normal = normal.normalize(); 
	Vector3 incidentRayDirection = (incidentRay.direction).normalize(); 
	

	//double sinIncidentAngle = sqrt(1 - pow(cosineOfIncidentAngle, 2.0)); 

	//if (sinIncidentAngle > (transmittedIndexOfRefraction / incomingIndexOfRefraction)) {
	// 	std::cout << "TIR occured" << std::endl; 
	//}

	Vector3 inverseNormal = (-1 * normal); 
	double indexOfRefractionRatio = incomingIndexOfRefraction / transmittedIndexOfRefraction; 
	double cosineOfIncidentAngle = normal.dot(incidentRayDirection); 

	double indexOfRefractionRatioSquared = pow(indexOfRefractionRatio, 2.0); 
	double cosineOfIncidentAngleSquared = pow(cosineOfIncidentAngle, 2.0); 

	Vector3 lhs = sqrt(1 - (indexOfRefractionRatioSquared * (1 - cosineOfIncidentAngleSquared))) * inverseNormal;
	Vector3 rhs = indexOfRefractionRatio * ((cosineOfIncidentAngle * normal) - incidentRayDirection);  

	Vector3 transmittedRayDirection = lhs + rhs; 
	transmittedRayDirection = transmittedRayDirection.normalize(); 

	/*
	Vector3 transmittedRayDirection = ((-1 * normal) 
							        * sqrt(1 - (pow((incomingIndexOfRefraction / transmittedIndexOfRefraction), 2.0) * (1 - pow(cosineOfIncidentAngle, 2.0))))) 
							        + ((incomingIndexOfRefraction / transmittedIndexOfRefraction) * ((cosineOfIncidentAngle * normal) - incidentRayDirection)); 

	*/ 						      

	transmittedRayDirection = transmittedRayDirection.normalize(); 
	intersectionPoint = intersectionPoint - (0.0001 * transmittedRayDirection); 
	return Ray(intersectionPoint, transmittedRayDirection); 

}