#include "TranslateAnimation.h"

TranslateAnimation::TranslateAnimation(DrawableObject* obj, glm::vec3 speed, glm::vec3 minPos, glm::vec3 maxPos)
    : translationSpeed(speed), minPosition(minPos), maxPosition(maxPos), direction(glm::vec3(1.0f)), accumulatedTranslation(glm::vec3(0.0f)) {
	this->object = obj;
}

void TranslateAnimation::update() {
    glm::vec3 translation = translationSpeed * direction;
    accumulatedTranslation += translation;

    for (int i = 0; i < 3; i++) {
        if (accumulatedTranslation[i] < minPosition[i] || accumulatedTranslation[i] > maxPosition[i]) {
            direction[i] *= -1.0f;
            accumulatedTranslation[i] = glm::clamp(accumulatedTranslation[i], minPosition[i], maxPosition[i]);
        }
    }

    Transform& transform = object->setTransform();
    transform.addTransformation(new Translate(translation));
}
