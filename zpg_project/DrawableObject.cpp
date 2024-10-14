#include "DrawableObject.h"

DrawableObject::DrawableObject(ShapeType shapeType) : model(nullptr), shader(nullptr) {
    this->shapeType = shapeType;
    this->transform = new Transform();
}

DrawableObject::~DrawableObject()
{
    delete model;
    delete shader;
    delete transform;
}

void DrawableObject::createShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, Camera* camera) {
    shader = ShaderFactory::createShader(vertexShaderPath, fragmentShaderPath, camera);
}

void DrawableObject::createModel() {
    model = ModelFactory::createModel(shapeType, glm::vec3(0.0f, 0.0f, 0.0f));
}

void DrawableObject::render() {
    shader->use();
    shader->setUniformLocation(transform->getModelMatrix());
    model->render(shapeType);
}

Transform& DrawableObject::getTransform() {
    return *transform;
}
