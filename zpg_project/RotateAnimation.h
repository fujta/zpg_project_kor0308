#pragma once
#include <glm/glm.hpp>
#include "Animation.h"
#include "DrawableObject.h"
#include "Rotate.h"

class RotateAnimation : public Animation
{
private:
    DrawableObject* object;
    float rotationSpeed;
    glm::vec3 rotationAxis;

public:
    RotateAnimation(DrawableObject* obj, float speed, glm::vec3 axis);
    void update() override;
};

