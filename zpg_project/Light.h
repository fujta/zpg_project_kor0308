#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "ILightObserver.h";

class Light
{
public:
	Light();
	~Light();

	void setPosition(const glm::vec3& position);
	void setColor(const glm::vec4& color);
	void setViewPosition(const glm::vec3& viewPosition);
	void setObjectColor(const glm::vec4& objectColor);
	void setShininess(float shininess);

	glm::vec3& getPosition();
	glm::vec4& getColor();
	glm::vec3& getViewPosition();
	glm::vec4& getObjectColor();
	float getShininess();

	void notifyObservers();
	void addObserver(ILightObserver* observer);
	void removeObserver(ILightObserver* observer);
private:
    glm::vec3 lightPosition;
    glm::vec4 lightColor;
    glm::vec3 viewPosition;
	glm::vec4 objectColor;
	float shininess;

	std::vector<ILightObserver*> observers;
};

