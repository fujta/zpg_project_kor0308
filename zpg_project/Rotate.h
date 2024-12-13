#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Transformation.h"

class Rotate : public Transformation
{
public:
    Rotate(float angleDegrees, const glm::vec3& axis)
        : angleDegrees(angleDegrees), axis(glm::normalize(axis)) {}

    glm::mat4 getMatrix() override;

protected:
    float angleDegrees;
    glm::vec3 axis;
};

