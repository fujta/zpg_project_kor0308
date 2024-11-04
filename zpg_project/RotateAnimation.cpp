#include "RotateAnimation.h"

RotateAnimation::RotateAnimation(DrawableObject* obj, float speed, glm::vec3 axis)
    : object(obj), rotationSpeed(speed), rotationAxis(axis) {}

void RotateAnimation::update() {
    object->setTransform().addTransformation(new Rotate(rotationSpeed, rotationAxis));
}