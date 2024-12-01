#include "Skybox.h"

Skybox::Skybox() : DrawableObject(ShapeType::SKYCUBE, "") {
	this->texture = new Texture("");
	this->texture->loadSkybox();
}

Skybox::~Skybox() {
}

void Skybox::createShaders(Camera* camera, Light* light) {
	shader = ShaderFactory::createShader("vertexShaderCubemap.glsl", "fragmentShaderCubemap.glsl", camera, light);
	shader->setSkyboxShader(true);
}

void Skybox::createModel() {
	model = ModelFactory::createModelWithSkybox(ShapeType::SKYCUBE);
}