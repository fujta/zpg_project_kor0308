#include "Camera.h"
#include <algorithm>

Camera::Camera(float aspectRatio)
    : position(glm::vec3(0.0f, 0.0f, 3.0f)),
    worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    fieldOfView(60.0f),
    zNear(0.1f),
    zFar(100.0f),
    aspectRatio(aspectRatio),
    horizontalAngle(-90.0f),
    verticalAngle(0.0f),
    movementSpeed(2.5f),
    mouseSensitivity(0.1f)
{
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(horizontalAngle)) * cos(glm::radians(verticalAngle));
    front.y = sin(glm::radians(verticalAngle));
    front.z = sin(glm::radians(horizontalAngle)) * cos(glm::radians(verticalAngle));
    target = glm::normalize(front);

    right = glm::normalize(glm::cross(target, worldUp));
    up = glm::normalize(glm::cross(right, target));

    notifyObservers();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, position + target, up);
}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::perspective(glm::radians(fieldOfView), aspectRatio, zNear, zFar);
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    horizontalAngle += xoffset;
    verticalAngle += yoffset;

    if (verticalAngle > 89.0f)
        verticalAngle = 89.0f;
    if (verticalAngle < -89.0f)
        verticalAngle = -89.0f;

    updateCameraVectors();
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;

    switch (direction) {
	    case FORWARD:
		    position += target * velocity;
		    break;
	    case BACKWARD:
		    position -= target * velocity;
		    break;
	    case LEFT:
		    position -= right * velocity;
		    break;
	    case RIGHT:
		    position += right * velocity;
		    break;
    }

    notifyObservers();
}

void Camera::addObserver(ICameraObserver* observer) {
    observers.push_back(observer);
}

void Camera::removeObserver(ICameraObserver* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Camera::notifyObservers() {
    for (auto observer : observers) {
        observer->onCameraUpdated();
    }
}

void Camera::setAspectRatio(float aspectRatio) {
    this->aspectRatio = aspectRatio;
    notifyObservers();
}
