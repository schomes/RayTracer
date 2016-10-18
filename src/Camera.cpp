#include "Camera.hpp"
#include <cmath>

// Camera::Camera(Point3 cameraPosition, Vector3 viewDirection, Vector3 upDirection, int imageWidth, int imageHeight, double verticalFieldOfView) {

// 	this->cameraPosition = cameraPosition;

// 	// Determine camera coordinate axes
// 	//... u is orthogonal to the viewingDirection
// 	//... v is orthogonal to the viewingDirection and u
// 	//...TODO: check if viewingDirection and upDirection are close to parallel
// 	//...TODO cont'd: more parallel means cross is closer to (0, 0, 0) (slide 6 - raycasting02.pdf)
// 	w = viewDirection.normalize();
// 	u = w.cross(upDirection);
// 	u = u.normalize();
// 	v = u.cross(w);
// 	v = v.normalize();


// 	// Determine corners of viewing window
// 	double aspectRatio = (double)(imageWidth) / imageHeight;
// 	double d = 15.0; // d is arbitrarily chosen
// 	double pi = 4 * atan(1.0);
// 	double radians = ((verticalFieldOfView / 2.0) * pi) / 180.0;
// 	double viewHeight = 2 * d * tan(radians);
// 	double viewWidth = aspectRatio * viewHeight;

// 	//... Viewing window corners
// 	ul = cameraPosition + (d * w) + (viewHeight / 2 * v) - (viewWidth / 2 * u);
// 	ur = cameraPosition + (d * w) + (viewHeight / 2 * v) + (viewWidth / 2 * u);
// 	ll = cameraPosition + (d * w) - (viewHeight / 2 * v) - (viewWidth / 2 * u);
// 	lr = cameraPosition + (d * w) - (viewHeight / 2 * v) + (viewWidth / 2 * u);

// 	// Horizontal offset per pixel
// 	hOffset = (ur - ul) / (imageWidth - 1.0);
// 	// Vertical offset per pixel
// 	vOffset = (ll - ul) / (imageHeight - 1.0);

// }