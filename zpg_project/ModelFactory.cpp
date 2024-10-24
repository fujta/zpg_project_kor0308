#include "ModelFactory.h"
#include "Model.h"

#include "sphere.h"
#include "bushes.h"
#include "tree.h"
#include "suzi_smooth.h"

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
		points = suziSmooth;
		pointCount = 17424;
	}
    else {
        std::cout << "Warning! Missing shape type in ModelFactory.cpp\n";
    }

    return new Model(points, pointCount);
}
