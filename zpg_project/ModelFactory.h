#ifndef MODEL_FACTORY_H
#define MODEL_FACTORY_H

#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <stdexcept>


using namespace std;

typedef struct ModelObject {
	float* points;
	int pointCount;
};

class Model;
class ModelWithTexture;
enum ShapeType { TRIANGLE, SQUARE, BUSH, TREE, SPHERE, PLAIN };

class ModelFactory {
public:
    static Model* createModel(ShapeType type, glm::vec3 position);
    static Model* createModelWithTexture(ShapeType type, glm::vec3 position);
	static ModelObject getModelObject(ShapeType type);
};

#endif
