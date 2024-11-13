#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(glm::vec3 direction);
	~DirectionalLight();

	void setDirection(glm::vec3 direction);
	glm::vec3 getDirection();

	std::string getFragmentShaderName();

private:
	glm::vec3 direction;
};

