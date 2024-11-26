#include "ModelFactory.h"
#include "Model.h"
#include "ModelWithTexture.h"

#include "sphere.h"
#include "bushes.h"
#include "tree.h"
#include "suzi_smooth.h"
#include "plain.h"

Model* ModelFactory::createModel(ShapeType type) {
	ModelObject modelObject = getModelObject(type);

    return new Model(modelObject.points, modelObject.pointCount);
}

Model* ModelFactory::createModelWithTexture(ShapeType type)
{
    ModelObject modelObject = getModelObject(type);

    cout << modelObject.pointCount << endl;

	return new ModelWithTexture(modelObject.points, modelObject.pointCount);
}

ModelObject ModelFactory::getModelObject(ShapeType type)
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
    else {
        throw new runtime_error("Missing model type");
    }

	ret.points = points;
	ret.pointCount = pointCount;

	return ret;
}


