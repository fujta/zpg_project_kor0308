#ifndef MODEL_FACTORY_H
#define MODEL_FACTORY_H

#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <stdexcept>


using namespace std;

typedef struct ModelObject {
	float* points;
	size_t pointCount;
};

class Model;
class ModelWithTexture;
class ObjectModel;

enum ShapeType { TRIANGLE, SQUARE, BUSH, TREE, SPHERE, PLAIN, SKYCUBE, OBJECT };

class ModelFactory {
public:
    static Model* createModel(ShapeType type);
    static Model* createModelWithTexture(ShapeType type);
    static Model* createModelWithSkybox(ShapeType type);
	static Model* createModelFromObj(std::string fileName);

	static ModelObject getModelVertexArray(ShapeType type);
};

#endif
