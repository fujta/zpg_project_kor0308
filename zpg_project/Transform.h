#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform {
public:
    Transform();

    Transform& setPosition(const glm::vec3& position);
    Transform& setRotation(float angleDegrees, const glm::vec3& axis);
    void rotate(float angleDegrees, const glm::vec3& axis);
    Transform& setScale(const glm::vec3& scale);

    glm::mat4 getModelMatrix() const;
	glm::vec3 getPosition() const;
    float getRotationAngle() const;

private:
    glm::vec3 position;
    glm::vec3 scale;
    glm::mat4 rotationMatrix;
    float rotationAngleDegrees;
};

