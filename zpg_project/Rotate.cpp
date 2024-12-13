#include "Rotate.h"

glm::mat4 Rotate::getMatrix()
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(angleDegrees), axis);
}
