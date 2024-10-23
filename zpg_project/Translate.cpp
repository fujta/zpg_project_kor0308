#include "Translate.h"

glm::mat4 Translate::apply(const glm::mat4& modelMatrix) const
{
	return glm::translate(modelMatrix, translation);
}
