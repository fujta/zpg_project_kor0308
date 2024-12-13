#include "DynamicTranslate.h"

void DynamicTranslate::update()
{
	translation += translationVelocity;

	if (translation.x < minPos.x || translation.x > maxPos.x)
	{
		translationVelocity.x *= -1;
	}

	if (translation.y < minPos.y || translation.y > maxPos.y)
	{
		translationVelocity.y *= -1;
	}

	if (translation.z < minPos.z || translation.z > maxPos.z)
	{
		translationVelocity.z *= -1;
	}
}

glm::mat4 DynamicTranslate::getMatrix()
{
	this->update();
	glm::mat4 result(1.0f);

	return glm::translate(result, translation);
}


