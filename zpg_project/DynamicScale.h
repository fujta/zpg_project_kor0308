#pragma once
#include "Scale.h"

class DynamicScale : public Scale
{
public:
	DynamicScale(const glm::vec3& scale, glm::vec3 scaleVelocity, glm::vec3 maxScale)
		: Scale(scale), scaleVelocity(scaleVelocity), maxScale(maxScale) {}

	glm::mat4 getMatrix() override;
	void update();

private:
	glm::vec3 scaleVelocity;
	glm::vec3 maxScale;
};

