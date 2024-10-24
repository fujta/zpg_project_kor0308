#include "TransformFacade.h"

TransformFacade::TransformFacade() : modelMatrix(1.0f) {}

TransformFacade::~TransformFacade() {
	for (Transformation* transformation : transformations) {
		delete transformation;
	}
}

TransformFacade& TransformFacade::addTransformation(Transformation* transformation)
{
	transformations.push_back(transformation);

	return *this;
}

glm::mat4 TransformFacade::getModelMatrix() const
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	for (Transformation* transformation : transformations) {
		modelMatrix = transformation->apply(modelMatrix);
	}

	return modelMatrix;
}