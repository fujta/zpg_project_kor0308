#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
	this->direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(glm::vec3 direction) : Light() 
{
	this->direction = direction;
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::setDirection(glm::vec3 direction)
{
	this->direction = direction;

	notifyObservers();
}

glm::vec3 DirectionalLight::getDirection()
{
	return direction;
}

std::string DirectionalLight::getFragmentShaderName()
{
	return "directionalLightFragmentShader.glsl";
}
