#include "ModelFactory.h"
#include "Model.h"

#include "sphere.h"
#include "bushes.h"
#include "tree.h"
#include "suzi_smooth.h"
#include "plain.h"

Model* ModelFactory::createModel(ShapeType type, glm::vec3 position) {
    float* points = nullptr;
    int pointCount = 0;

    if (type == BUSH) {
        points = bushes;
        pointCount = 26190;
    }
    else if (type == TREE) {
        points = tree;
		pointCount = 610814;
	}
	else if (type == SPHERE) {
		points = sphere;
		pointCount = 20520;
    }
	else if (type == PLAIN) {
		points = plain;
		pointCount = 36;
	}
    else {
        throw new runtime_error("Missing model type");
    }

    return new Model(points, pointCount);
}

Model* ModelFactory::createModelWithTexture(ShapeType type, glm::vec3 position)
{
    throw new runtime_error("Not implemented yet");
    //return nullptr;
}
