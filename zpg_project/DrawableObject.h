#pragma once

#include "Model.h"
#include "Shader.h"
#include "ShaderFactory.h"
#include "TransformFacade.h"
#include "Texture.h"

class DrawableObject
{
public:
    DrawableObject(ShapeType shapeType, const std::string& texturePath = "");
    ~DrawableObject();

    void render();

    void createShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, Camera* camera, Light* light = nullptr);
	void createShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, Camera* camera, std::vector<Light*> lights);

    void createShaders(Shader* shader);

    void createModel();

    TransformFacade& setTransform();

    bool isSkybox() const;

private:
    ShapeType shapeType;
    TransformFacade* transformFacade;

protected:
    Model* model;
    Shader* shader;
    Texture* texture;

};
