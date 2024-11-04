#include "DrawableObject.h"

DrawableObject::DrawableObject(ShapeType shapeType) : model(nullptr), shader(nullptr) {
    this->shapeType = shapeType;
    this->transformFacade = new TransformFacade();
}

DrawableObject::~DrawableObject()
{
    delete model;
    delete shader;
    delete transformFacade;
}

void DrawableObject::createShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, Camera* camera, Light* light) {
    shader = ShaderFactory::createShader(vertexShaderPath, fragmentShaderPath, camera, light);
}

void DrawableObject::createShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, Camera* camera, std::vector<Light*> lights) {
    shader = ShaderFactory::createShader(vertexShaderPath, fragmentShaderPath, camera, lights);
}

void DrawableObject::createShaders(Shader* shader) {
    this->shader = shader;
}

void DrawableObject::createModel() {
    model = ModelFactory::createModel(shapeType, glm::vec3(0.0f, 0.0f, 0.0f));
}

void DrawableObject::render() {
    if (shader) {
        shader->use();
        shader->setUniformMatrix(transformFacade->getModelMatrix());
        model->render(shapeType);
    }
    else {
        std::cerr << "Shader is nullptr, cannot render DrawableObject." << std::endl;
    }
}

TransformFacade& DrawableObject::setTransform() {
    return *transformFacade;
}
