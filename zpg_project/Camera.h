#pragma once
#include <glm/fwd.hpp>
#include <glm/ext/matrix_transform.hpp>

class Camera
{
private:
	float fieldOfView;
	glm::vec3 lookPoint;
	glm::vec3 position;

	float zNear;
	float zFar;
public:
	glm::mat4 Camera::getCamera(eye, eye + target, up);
};

