#include "Translate.h"

glm::mat4 Translate::getMatrix()
{
	return glm::translate(glm::mat4(1.0f), translation);
}
