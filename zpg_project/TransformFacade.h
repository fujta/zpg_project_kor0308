#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "Transformation.h"

using namespace std;

class TransformFacade {
public:
	TransformFacade();
	~TransformFacade();

	TransformFacade& addTransformation(Transformation* transformation);

    glm::mat4 getModelMatrix() const;

private:
	glm::mat4 modelMatrix;
	vector<Transformation*> transformations;
};
