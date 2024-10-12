#ifndef MODEL_FACTORY_H
#define MODEL_FACTORY_H

#include <glm/ext/vector_float3.hpp>
#include <iostream>

class Model;
enum ShapeType { TRIANGLE, SQUARE, BUSH, TREE };

class ModelFactory {
public:
    static Model* createModel(ShapeType type, glm::vec3 position);
};

#endif
