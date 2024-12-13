#pragma once

#include <glm/glm.hpp>

class Transformation
{
public:
	virtual ~Transformation() = default;
	virtual glm::mat4 getMatrix() = 0;
};

