#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include "ModelFactory.h"

class Model {
protected:
    GLuint VBO, VAO;
    float* points;
    GLsizeiptr pointCount;

public:
    Model(float* points, GLsizeiptr pointCount);
    Model();
    ~Model();
    virtual void render(ShapeType shapeType);
};

#endif
