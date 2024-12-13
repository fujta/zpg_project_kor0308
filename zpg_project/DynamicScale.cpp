#include "DynamicScale.h"

void DynamicScale::update()
{
    if (scale.x >= maxScale.x && scale.y >= maxScale.y && scale.z >= maxScale.z) {
        return;
    }

    scale.x += scaleVelocity.x;
    scale.y += scaleVelocity.y;
    scale.z += scaleVelocity.z;
}

glm::mat4 DynamicScale::getMatrix()
{
    this->update();
    glm::mat4 result(1.0f);

    return glm::scale(result, scale);
}


