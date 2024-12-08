#include "DrawableObject.h"

DrawableObject::DrawableObject(ShapeType shapeType, const std::string& texturePath, const std::string& p_objPath) : model(nullptr), shader(nullptr) {
    this->shapeType = shapeType;
    this->transformFacade = new TransformFacade();
	this->objPath = p_objPath;

    this->id = nextId++;
    if (texturePath != "") {
        this->texture = new Texture(texturePath);
        texture->load();
    }
    else {
		this->texture = nullptr;
    }
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
    if (this->texture == nullptr) {
        model = ModelFactory::createModel(shapeType);
    } else if (this->texture != nullptr && this->objPath != "") {
		model = ModelFactory::createModelFromObj(objPath);
    }
    else {
        model = ModelFactory::createModelWithTexture(shapeType);
    }
}

bool DrawableObject::isSkybox() const {
    return shapeType == SKYCUBE;
}

void DrawableObject::render() {
    if (shader) {
        shader->use();
        shader->setUniformMatrix(transformFacade->getModelMatrix());
        shader->useTexture(texture);
        model->render(shapeType);

		texture->unbind();
		shader->unuse();
    }
    else {
        std::cerr << "Shader is nullptr, cannot render DrawableObject." << std::endl;
    }
}

TransformFacade& DrawableObject::setTransform() {
    return *transformFacade;
}

int DrawableObject::nextId = 1;

void DrawableObject::setId(int id) {
	this->id = id;
}

int DrawableObject::getId() {
    return this->id;
}
