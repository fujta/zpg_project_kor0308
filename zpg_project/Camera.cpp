#include "Camera.h"

glm::mat4 Camera::getCamera(void) {
	return glm::lookAt(eye, eye + target, up);
}
