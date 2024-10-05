#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

class Model {
private:
    GLuint VBO, VAO;
    float* points;
    int pointCount;

public:
    Model(float* points, int pointCount);
    ~Model();
    void render();
};

#endif
