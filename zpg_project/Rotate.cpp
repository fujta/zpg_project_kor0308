#include "Rotate.h"

glm::mat4 Rotate::apply(const glm::mat4& modelMatrix) const
{
	return glm::rotate(modelMatrix, glm::radians(angleDegrees), axis);
}
