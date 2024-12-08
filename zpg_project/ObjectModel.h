#pragma once
#include <iostream>
#include <glm/glm.hpp>

#include "Model.h"

struct Vertex
{
    float Position[3];
    float Normal[3];
    float Texture[2];
    float Tangent[3];
};

class ObjectModel : public Model
{
public:
	ObjectModel(std::string fileName);
	~ObjectModel();

	void render(ShapeType shapeType) override;

private:
	GLuint IBO;
    int indicesCount;
};

