#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Transformation.h"

class Scale : public Transformation
{
public:
    Scale(const glm::vec3& scale) : scale(scale) {}

    glm::mat4 getMatrix() override;

protected:
    glm::vec3 scale;
};

