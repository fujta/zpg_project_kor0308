#pragma once

#include <glm/glm.hpp>

class Transformation
{
public:
	virtual ~Transformation() = default;
	virtual glm::mat4 apply(const glm::mat4& modelMatrix) const = 0;
};

