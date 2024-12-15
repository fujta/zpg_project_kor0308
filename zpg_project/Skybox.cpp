#include "Skybox.h"

Skybox::Skybox(Camera* camera) : DrawableObject(ShapeType::SKYCUBE, "") {
	this->texture = new Texture("");
	this->texture->loadSkybox();
	this->camera = camera;
	this->camera->addObserver(this);
}

Skybox::~Skybox() {
}

void Skybox::createShaders(Camera* camera, Light* light) {
	shader = ShaderFactory::createShader("lightVertexShader.glsl", "fragmentShaderCubemap.glsl", camera, light);
	shader->setSkyboxShader(true);
}

void Skybox::createModel() {
	model = ModelFactory::createModelWithSkybox(ShapeType::SKYCUBE);
}

void Skybox::onCameraUpdated() {
	this->setTransform().removeTransformations();
	this->setTransform().addTransformation(new Translate(camera->getPosition()));
}

void Skybox::setFollowCamera(bool followCamera)
{
	this->followCamera = followCamera;
}

bool Skybox::getFollowCamera()
{
	return followCamera;
}
