#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "ILightObserver.h";
#include "Material.h";

class Material;

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
	Material* getMaterial();

	void notifyObservers();
	void addObserver(ILightObserver* observer);
	void removeObserver(ILightObserver* observer);

	std::string virtual getFragmentShaderName() = 0;
private:
    glm::vec3 lightPosition;
    glm::vec4 lightColor;
    glm::vec3 viewPosition;
	glm::vec4 objectColor;
	float shininess;

	Material* material;

	std::vector<ILightObserver*> observers;
};

