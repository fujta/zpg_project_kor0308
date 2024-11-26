#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include "ModelFactory.h"

class Model {
protected:
    GLuint VBO, VAO;
    float* points;
    int pointCount;

public:
    Model(float* points, int pointCount);
    Model();
    ~Model();
    void render(ShapeType shapeType);
};

#endif
