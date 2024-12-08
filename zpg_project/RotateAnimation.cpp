#include "RotateAnimation.h"

RotateAnimation::RotateAnimation(DrawableObject* obj, float speed, glm::vec3 axis)
    : rotationSpeed(speed), rotationAxis(axis) {
	this->object = obj;
}

void RotateAnimation::update() {
    object->setTransform().addTransformation(new Rotate(rotationSpeed, rotationAxis));
}