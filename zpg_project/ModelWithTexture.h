#pragma once
#include "Model.h"

class ModelWithTexture : public Model
{
public:
	ModelWithTexture(float* points, GLsizeiptr pointCount);
	~ModelWithTexture();
};

