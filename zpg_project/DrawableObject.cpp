#include "DrawableObject.h"

DrawableObject::DrawableObject(ShapeType shapeType) : model(nullptr), shader(nullptr) {
    this->shapeType = shapeType;
    this->transform = new TransformFacade();
}

DrawableObject::~DrawableObject()
{
    delete model;
    delete shader;
    delete transform;
}

void DrawableObject::createShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, Camera* camera, Light* light) {
    shader = ShaderFactory::createShader(vertexShaderPath, fragmentShaderPath, camera, light);
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
        shader->setUniformLocation(transform->getModelMatrix());
        model->render(shapeType);
    }
    else {
        std::cerr << "Shader is nullptr, cannot render DrawableObject." << std::endl;
    }
}

TransformFacade& DrawableObject::setTransform() {
    return *transform;
}
