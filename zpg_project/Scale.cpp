#include "Scale.h"

glm::mat4 Scale::apply(const glm::mat4& modelMatrix) const
{
	return glm::scale(modelMatrix, scale);
}
