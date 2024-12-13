#pragma once
#include "Translate.h"

class DynamicTranslate : public Translate
{
public:
	DynamicTranslate(const glm::vec3& translation, glm::vec3 translationVelocity, glm::vec3 minPos, glm::vec3 maxPos)
		: Translate(translation), translationVelocity(translationVelocity), minPos(minPos), maxPos(maxPos){}

	glm::mat4 getMatrix() override;
	void update();

private:
	glm::vec3 translationVelocity;
	glm::vec3 minPos, maxPos;
};

