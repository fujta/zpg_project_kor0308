#include "Light.h"

#include <iostream>

Light::Light()
{
	lightPosition = glm::vec3(0.0f, 10.0f, 0.0f);
	lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	objectColor = glm::vec4(0.5f, 0.5f, 1.0f, 1.0f);
	shininess = 32.0f;
}

Light::~Light()
{
}

void Light::setPosition(const glm::vec3& position)
{
	lightPosition = position;

	notifyObservers();
}

void Light::setColor(const glm::vec4& color)
{
	lightColor = color;

	notifyObservers();
}

void Light::setViewPosition(const glm::vec3& viewPosition)
{
	this->viewPosition = viewPosition;

	notifyObservers();
}

void Light::setObjectColor(const glm::vec4& objectColor)
{
	this->objectColor = objectColor;

	notifyObservers();
}

void Light::setShininess(float shininess)
{
	this->shininess = shininess;

	notifyObservers();
}

glm::vec3& Light::getPosition()
{
	return lightPosition;
}

glm::vec4& Light::getColor()
{
	return lightColor;
}

glm::vec3& Light::getViewPosition()
{
	return viewPosition;
}

glm::vec4& Light::getObjectColor()
{
	return objectColor;
}

float Light::getShininess()
{
	return shininess;
}

void Light::notifyObservers()
{
	for (auto observer : observers) {
		observer->onLightUpdated();
	}
}

void Light::addObserver(ILightObserver* observer)
{
	observers.push_back(observer);
	std::cout << "Observer added: " << observer << std::endl;
}

void Light::removeObserver(ILightObserver* observer)
{
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}


