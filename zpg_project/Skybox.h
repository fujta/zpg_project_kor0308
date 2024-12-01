#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include "DrawableObject.h"

class Skybox : public DrawableObject
{
public:
	Skybox();
	~Skybox();

	void createShaders(Camera* camera, Light* light);
	void createModel();
};

