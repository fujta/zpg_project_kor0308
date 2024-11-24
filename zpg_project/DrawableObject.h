#pragma once

#include "Model.h"
#include "Shader.h"
#include "ShaderFactory.h"
#include "TransformFacade.h"
#include "Texture.h"

class DrawableObject
{
public:
    DrawableObject(ShapeType shapeType);
    ~DrawableObject();

    void render();
    void createShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, Camera* camera, Light* light = nullptr);
	void createShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, Camera* camera, std::vector<Light*> lights);
    void createShaders(Shader* shader);
    void createModel(const std::string& texturePath = "");
    TransformFacade& setTransform();

private:
    ShapeType shapeType;
    Model* model;
    Shader* shader;
    TransformFacade* transformFacade;
    Texture* texture;
};
