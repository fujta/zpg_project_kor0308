#include "ModelFactory.h"

#include "Model.h"
#include "ModelWithTexture.h"
#include "ModelSkybox.h"
#include "ObjectModel.h"

#include "sphere.h"
#include "bushes.h"
#include "tree.h"
#include "suzi_smooth.h"
#include "plain.h"
#include "skycube.h"

Model* ModelFactory::createModel(ShapeType type) {
	ModelObject modelObject = getModelVertexArray(type);

    return new Model(modelObject.points, modelObject.pointCount);
}

Model* ModelFactory::createModelWithTexture(ShapeType type)
{
    ModelObject modelObject = getModelVertexArray(type);


	return new ModelWithTexture(modelObject.points, modelObject.pointCount);
}

Model* ModelFactory::createModelWithSkybox(ShapeType type)
{
    ModelObject modelObject = getModelVertexArray(type);

    return new ModelSkybox(modelObject.points, modelObject.pointCount);
}

Model* ModelFactory::createModelFromObj(std::string fileName)
{
	return new ObjectModel(fileName);
}

ModelObject ModelFactory::getModelVertexArray(ShapeType type)
{
    float* points = nullptr;
    GLsizeiptr pointCount;
    ModelObject ret;

    if (type == BUSH) {
        points = bushes;
        pointCount = sizeof(bushes);
    }
    else if (type == TREE) {
        points = tree;
        pointCount = sizeof(tree);
    }
    else if (type == SPHERE) {
        points = sphere;
        pointCount = sizeof(sphere);
    }
    else if (type == PLAIN) {
        points = plain;
        pointCount = sizeof(plain);
    }
    else if (type == SKYCUBE) {
		points = skycube;
		pointCount = sizeof(skycube);

    }
    else {
        throw new runtime_error("Missing model type");
    }

	ret.points = points;
	ret.pointCount = pointCount;

	return ret;
}


