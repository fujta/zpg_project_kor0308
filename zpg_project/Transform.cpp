#include "Transform.h"

Transform::Transform()
    : position(0.0f), rotationAngleDegrees(0.0f), rotationAxis(0.0f, 1.0f, 0.0f), scale(1.0f) {}

Transform& Transform::setPosition(const glm::vec3& pos) {
    position = pos;

    return *this;
}

Transform& Transform::setRotation(float angleDegrees, const glm::vec3& axis) {
    rotationAngleDegrees = angleDegrees;
    rotationAxis = glm::normalize(axis);

    return *this;
}

void Transform::rotate(float angleDegrees, const glm::vec3& axis) {
    rotationAngleDegrees += angleDegrees;
    rotationAxis = glm::normalize(axis);
}

Transform& Transform::setScale(const glm::vec3& scl) {
    scale = scl;

    return *this;
}

glm::mat4 Transform::getModelMatrix() const {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
    model = model * glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleDegrees), rotationAxis);
    model = glm::scale(model, scale);

    return model;
}

glm::vec3 Transform::getPosition() const {
    return position;
}

float Transform::getRotationAngle() const {
    return rotationAngleDegrees;
}
