#include "Transform.h"

Transform::Transform() {}

Transform::~Transform() {
	for (Transformation* transformation : transformations) {
		delete transformation;
	}
}

Transform& Transform::addTransformation(Transformation* transformation)
{
	transformations.push_back(transformation);

	return *this;
}

glm::mat4 Transform::getModelMatrix() const
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	for (Transformation* transformation : transformations) {
		modelMatrix *= transformation->getMatrix();
	}

	return modelMatrix;
}