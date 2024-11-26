#include "ModelFactory.h"
#include "Model.h"
#include "ModelWithTexture.h"

#include "sphere.h"
#include "bushes.h"
#include "tree.h"
#include "suzi_smooth.h"
#include "plain.h"

Model* ModelFactory::createModel(ShapeType type, glm::vec3 position) {
	ModelObject modelObject = getModelObject(type);

    return new Model(modelObject.points, modelObject.pointCount);
}

Model* ModelFactory::createModelWithTexture(ShapeType type, glm::vec3 position)
{
    ModelObject modelObject = getModelObject(type);

	return new ModelWithTexture(modelObject.points, modelObject.pointCount);
}

ModelObject ModelFactory::getModelObject(ShapeType type)
{
    float* points = nullptr;
    int pointCount = 0;

    if (type == BUSH) {
        points = bushes;
        pointCount = 26190;
    }
    else if (type == TREE) {
        points = tree;
        pointCount = 550814;
    }
    else if (type == SPHERE) {
        points = sphere;
        pointCount = 20520;
    }
    else if (type == PLAIN) {
        points = plain;
        pointCount = 192;
    }
    else {
        throw new runtime_error("Missing model type");
    }

	return { points, pointCount };
}


