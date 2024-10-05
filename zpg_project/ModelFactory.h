#ifndef MODEL_FACTORY_H
#define MODEL_FACTORY_H

#include <glm/ext/vector_float3.hpp>

class Model;
enum ShapeType { TRIANGLE, SQUARE };

class ModelFactory {
public:
    static Model* createModel(ShapeType type, glm::vec3 position);
};

#endif
