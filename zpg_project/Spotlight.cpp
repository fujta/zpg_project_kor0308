#include "Spotlight.h"

Spotlight::Spotlight(Camera* camera)
    : direction(glm::vec3(0.0f, -1.0f, 0.0f)), cutOff(glm::cos(glm::radians(12.5f))), outerCutOff(glm::cos(glm::radians(17.5f))) {

    if (camera) {
	    this->camera = camera;
	    camera->addObserver(this);
    }
}

Spotlight::~Spotlight() {
}

void Spotlight::setDirection(const glm::vec3& direction) {
    this->direction = glm::normalize(direction);
    notifyObservers();
}

void Spotlight::setCutOff(float cutOff) {
    this->cutOff = glm::cos(glm::radians(cutOff));
    notifyObservers();
}

void Spotlight::setOuterCutOff(float outerCutOff) {
    this->outerCutOff = glm::cos(glm::radians(outerCutOff));
    notifyObservers();
}

glm::vec3& Spotlight::getDirection() {
    return direction;
}

float Spotlight::getCutOff() {
    return cutOff;
}

float Spotlight::getOuterCutOff() {
    return outerCutOff;
}

std::string Spotlight::getFragmentShaderName() {
    return "spotlightFragmentShader.glsl";
}

void Spotlight::onCameraUpdated()
{
	this->setDirection(camera->getTarget());
	this->setPosition(camera->getPosition());
}
