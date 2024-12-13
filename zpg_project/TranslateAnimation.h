#pragma once

#include <glm/glm.hpp>
#include "Animation.h"
#include "DrawableObject.h"
#include "Transform.h"
#include "Translate.h"

class TranslateAnimation : public Animation {
protected:
    glm::vec3 translationSpeed;

private:
    glm::vec3 minPosition, maxPosition;
    glm::vec3 accumulatedTranslation;
    glm::vec3 direction;

public:
    TranslateAnimation(DrawableObject* obj, glm::vec3 speed, glm::vec3 minPos, glm::vec3 maxPos);
    void update() override;
};




