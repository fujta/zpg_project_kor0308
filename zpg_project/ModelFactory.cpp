#include "ModelFactory.h"
#include "Model.h"

Model* ModelFactory::createModel(ShapeType type, glm::vec3 position) {
    float* points = nullptr;
    int pointCount = 0;

    if (type == TRIANGLE) {
        static float trianglePoints[] = {
            position.x + 0.0f, position.y + 0.5f, 0.0f,
            position.x + 0.5f, position.y - 0.5f, 0.0f,
            position.x + -0.5f, position.y - 0.5f, 0.0f
        };
        points = trianglePoints;
        pointCount = 9;
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
