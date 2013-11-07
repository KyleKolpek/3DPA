#include "Viewport.h"

Viewport::Viewport(int width, int height):
    width(width),
    height(height),
    camera()
{
	// Set up camera
	camera.perspective(45.0, 1.0, 0.01, 200.0); 
	camera.setAt(glm::vec3(0.0));
	camera.setEye(glm::vec3(0.0, 0.0, 10.0));
	camera.setUp(glm::vec3(0.0, 1.0, 0.0));
}

Viewport::~Viewport()
{
}

ThirdPersonCamera& Viewport::getCurrentCamera()
{
    return camera;
}
