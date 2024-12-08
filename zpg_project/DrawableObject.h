#pragma once

#include "Model.h"
#include "Shader.h"
#include "ShaderFactory.h"
#include "TransformFacade.h"
#include "Texture.h"

class DrawableObject
{
public:
    DrawableObject(ShapeType shapeType, const std::string& texturePath = "", const std::string& p_objPath = "");
    ~DrawableObject();

    void render();

    void createShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, Camera* camera, Light* light = nullptr);
	void createShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, Camera* camera, std::vector<Light*> lights);

    void createShaders(Shader* shader);

    void createModel();

    TransformFacade& setTransform();

    bool isSkybox() const;

    void setId(int id);
    int getId();

private:
    ShapeType shapeType;
    TransformFacade* transformFacade;
    std::string objPath;

	int id;

protected:
    Model* model;
    Shader* shader;
    Texture* texture;

};
