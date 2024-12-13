#pragma once
#include "Rotate.h"

class DynamicRotate : public Rotate
{
public:
	DynamicRotate(float angleDegrees, const glm::vec3& axis, float rotateVelocity) : Rotate(angleDegrees, axis), rotateVelocity(rotateVelocity) {}

	glm::mat4 getMatrix() override;
	void update();

private:
	float rotateVelocity;

};

