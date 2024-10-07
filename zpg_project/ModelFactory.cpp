#include "ModelFactory.h"
#include "Model.h"

#include "sphere.h"
#include "bushes.h"

Model* ModelFactory::createModel(ShapeType type, glm::vec3 position) {
    float* points = nullptr;
    int pointCount = 0;

    if (type == TRIANGLE) {
        //static float a[] = {
        //     -.5f, -.5f, .5f,  0, 0, 1,
        //     -.5f, .5f, .5f,  0, 0, 1,
        //       .5f, .5f, .5f,  0, 0, 1,
        //       .5f, -.5f, .5f,  0, 0, 1 };
        points = bushes;
        pointCount = 26190;
    }
    else if (type == SQUARE) {
        static float squarePoints[] = {
            position.x - 0.25f, position.y + 0.25f, 0.0f, // top left
            position.x + 0.25f, position.y + 0.25f, 0.0f, // top right
            position.x - 0.25f, position.y - 0.25f, 0.0f, // bottom left
            position.x + 0.25f, position.y - 0.25f, 0.0f  // bottom right
        };
        points = squarePoints;
        pointCount = 12;
    }

    return new Model(points, pointCount);
}
