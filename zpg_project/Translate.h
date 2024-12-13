#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Transformation.h"

class Translate : public Transformation
{
public:
    Translate(const glm::vec3& translation) : translation(translation) {}
    glm::mat4 getMatrix() override;

protected:
    glm::vec3 translation;
};

