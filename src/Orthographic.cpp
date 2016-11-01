#include "Orthographic.hpp"
#include <cmath>

Orthographic::Orthographic(Point3 cameraPosition, Vector3 viewDirection, Vector3 upDirection, int imageWidth, int imageHeight, double verticalFieldOfView, double distance) {

	this->cameraPosition = cameraPosition;

	// Determine camera coordinate axes
	//... u is orthogonal to the viewingDirection
	//... v is orthogonal to the viewingDirection and u
	//...TODO: check if viewingDirection and upDirection are close to parallel
	//...TODO cont'd: more parallel means cross is closer to (0, 0, 0) (slide 6 - raycasting02.pdf)
	w = viewDirection.normalize();
	u = w.cross(upDirection);
	u = u.normalize();
	v = u.cross(w);
	v = v.normalize();


	// Determine corners of viewing window
	double aspectRatio = (double)(imageWidth) / imageHeight;
	//double d = 15.0; // d is arbitrarily chosen
	double pi = 4 * atan(1.0);
	double radians = ((verticalFieldOfView / 2.0) * pi) / 180.0;
	double viewHeight = 2 * distance * tan(radians);
	double viewWidth = aspectRatio * viewHeight;

	//... Viewing window corners
	ul = cameraPosition + (viewHeight / 2 * v) - (viewWidth / 2 * u);
	ur = cameraPosition + (viewHeight / 2 * v) + (viewWidth / 2 * u);
	ll = cameraPosition - (viewHeight / 2 * v) - (viewWidth / 2 * u);
	lr = cameraPosition - (viewHeight / 2 * v) + (viewWidth / 2 * u);

	// Horizontal offset per pixel
	hOffset = (ur - ul) / (imageWidth - 1.0);
	// Vertical offset per pixel
	vOffset = (ll - ul) / (imageHeight - 1.0);

}

Ray Orthographic::getRay(int x, int y) {
	Point3 viewingWindowPoint = ul + (vOffset * y) + (hOffset * x);
	return Ray(viewingWindowPoint, w);
}