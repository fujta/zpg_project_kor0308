#include "DynamicRotate.h"

glm::mat4 DynamicRotate::getMatrix()
{
    this->update();
    glm::mat4 result(1.0f);

	return glm::rotate(result, glm::radians(angleDegrees), axis);
}

void DynamicRotate::update()
{
	angleDegrees += rotateVelocity;
}
