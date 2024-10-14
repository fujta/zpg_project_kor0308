#pragma once

#include "Model.h"
#include "Shader.h"
#include "ShaderFactory.h"
#include "Transform.h"

class DrawableObject
{
public:
    DrawableObject(ShapeType shapeType);
    ~DrawableObject();

    void render();
    void createShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, Camera* camera);
    void createModel();
    Transform& getTransform();

private:
    ShapeType shapeType;
    Model* model;
    Shader* shader;
    Transform* transform;
};
