#include "Transform.h"

Transform::Transform()
    : position(0.0f), scale(1.0f), rotationMatrix(1.0f) {}

void Transform::setPosition(const glm::vec3& pos) {
    position = pos;
}

void Transform::setRotation(float angleDegrees, const glm::vec3& axis) {
    rotationAngleDegrees = angleDegrees;
    rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angleDegrees), glm::normalize(axis));
}

void Transform::rotate(float angleDegrees, const glm::vec3& axis) {
    rotationAngleDegrees += angleDegrees;
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(angleDegrees), glm::normalize(axis));
}

void Transform::setScale(const glm::vec3& scl) {
    scale = scl;
}

glm::mat4 Transform::getModelMatrix() const {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
    model *= rotationMatrix;
    model = glm::scale(model, scale);

    return model;
}

glm::vec3 Transform::getPosition() const {
	return position;
}

float Transform::getRotationAngle() const {
    return rotationAngleDegrees;
}