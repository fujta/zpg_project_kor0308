#pragma once

#include "Model.h"
#include "Shader.h"
#include "ShaderFactory.h"
#include "TransformFacade.h"

class DrawableObject
{
public:
    DrawableObject(ShapeType shapeType);
    ~DrawableObject();

    void render();
    void createShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, Camera* camera, Light* light = nullptr);
    void createShaders(Shader* shader);
    void createModel();
    TransformFacade& setTransform();

private:
    ShapeType shapeType;
    Model* model;
    Shader* shader;
    TransformFacade* transform;
};
