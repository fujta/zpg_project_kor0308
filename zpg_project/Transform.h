#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "Transformation.h"

using namespace std;

class Transform {
public:
	Transform();
	~Transform();

	Transform& addTransformation(Transformation* transformation);

    glm::mat4 getModelMatrix() const;

	void removeTransformations();

private:
	vector<Transformation*> transformations;
};
