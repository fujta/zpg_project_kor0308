#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Transformation.h"

class Scale : public Transformation
{
public:
    Scale(const glm::vec3& scale) : scale(scale) {}

    glm::mat4 apply(const glm::mat4& modelMatrix) const override;

private:
    glm::vec3 scale;
};

