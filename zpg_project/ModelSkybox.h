#pragma once

#include "Model.h"

class ModelSkybox : public Model
{
public:
	ModelSkybox(float* points, GLsizeiptr pointCount);
	~ModelSkybox();
};

