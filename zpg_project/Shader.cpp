#include "Shader.h"
#include <iostream>

Shader::Shader(Camera* camera, Light* light, const string& vertexShaderPath, const string& fragmentShaderPath) {
    shaderProgram = 0;

	this->setCamera(camera);
	this->addLight(light);

    this->camera = camera;
    camera->addObserver(this);

    this->light = light;
    if (light) {
        this->light->addObserver(this);
    }
     
    shaderLoader = new ShaderLoader(vertexShaderPath.c_str(), fragmentShaderPath.c_str(), &shaderProgram);
    viewMatrixLoc = glGetUniformLocation(shaderProgram, "viewMatrix");
    projectionMatrixLoc = glGetUniformLocation(shaderProgram, "projectionMatrix");
    onCameraUpdated();
}

Shader::~Shader() {
    if (shaderProgram != 0) {
        glDeleteProgram(shaderProgram);
    }

    camera->removeObserver(this);
    if (light) {
        light->removeObserver(this);
    }

	shaderLoader->deleteShader();
	delete shaderLoader;
}

void Shader::addLight(Light* light) {
    if (!light) return;
    this->light = light;
    light->addObserver(this);
    onLightUpdated();
}

void Shader::setCamera(Camera* camera) {
    if (this->camera) {
        this->camera->removeObserver(this);
    }

    this->camera = camera;

    if (camera) {
        camera->addObserver(this);
        onCameraUpdated();
    }
}

void Shader::unuse()
{
	glUseProgram(0);
}

void Shader::useTexture(Texture* texture)
{
    if (texture && texture->getTextureID() != 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
        glUniform1i(glGetUniformLocation(shaderProgram, "textureUnitID"), 0);
        glUniform1i(glGetUniformLocation(shaderProgram, "hasTexture"), GL_TRUE);
    }
    else {
        glUniform1i(glGetUniformLocation(shaderProgram, "hasTexture"), GL_FALSE);
    }
}

void Shader::onCameraUpdated() {
    this->use();

    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = camera->getProjectionMatrix();
    glm::vec3 viewPosition = camera->getPosition();

    glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3fv(glGetUniformLocation(shaderProgram, "viewPosition"), 1, glm::value_ptr(viewPosition));
}

void Shader::onLightUpdated() {
    if (!light) return;

    this->use();

    updateCommonLightUniforms();
    updateMaterialUniforms();

    if (Spotlight* spotlight = dynamic_cast<Spotlight*>(light)) {
        updateSpotlightUniforms(spotlight);
    }
    else if (DirectionalLight* directional = dynamic_cast<DirectionalLight*>(light)) {
        updateDirectionalLightUniforms(directional);
    }
    else {
        updatePointLightUniforms();
    }
}

void Shader::updateCommonLightUniforms() {
    glm::vec3 lightPosition = light->getPosition();
    glm::vec4 lightColor = light->getColor();
    glm::vec3 viewPosition = camera->getPosition();
    glm::vec4 objectColor = light->getObjectColor();
    float shininess = light->getShininess();

    glUniform3fv(glGetUniformLocation(shaderProgram, "lightPosition"), 1, glm::value_ptr(lightPosition));
    glUniform4fv(glGetUniformLocation(shaderProgram, "lightColor"), 1, glm::value_ptr(lightColor));
    glUniform3fv(glGetUniformLocation(shaderProgram, "viewPosition"), 1, glm::value_ptr(viewPosition));
    glUniform4fv(glGetUniformLocation(shaderProgram, "objectColor"), 1, glm::value_ptr(objectColor));
    glUniform1f(glGetUniformLocation(shaderProgram, "shininess"), shininess);
    glUniform1i(glGetUniformLocation(shaderProgram, "numberOfLights"), 1);
}

void Shader::updateMaterialUniforms() {
    glUniform1f(glGetUniformLocation(shaderProgram, "lights[0].material.ra"), light->getMaterial()->getRa());
    glUniform1f(glGetUniformLocation(shaderProgram, "lights[0].material.rd"), light->getMaterial()->getRd());
    glUniform1f(glGetUniformLocation(shaderProgram, "lights[0].material.rs"), light->getMaterial()->getRs());
}

void Shader::updateSpotlightUniforms(Spotlight* spotlight) {
    glUniform3fv(glGetUniformLocation(shaderProgram, "spotlight.position"), 1, glm::value_ptr(spotlight->getPosition()));
    glUniform3fv(glGetUniformLocation(shaderProgram, "spotlight.direction"), 1, glm::value_ptr(spotlight->getDirection()));
    glUniform4fv(glGetUniformLocation(shaderProgram, "spotlight.color"), 1, glm::value_ptr(spotlight->getColor()));
    glUniform1f(glGetUniformLocation(shaderProgram, "spotlight.cutOff"), spotlight->getCutOff());
    glUniform1f(glGetUniformLocation(shaderProgram, "spotlight.outerCutOff"), spotlight->getOuterCutOff());

    // Set attenuation factors to default values
    glUniform1f(glGetUniformLocation(shaderProgram, "spotlight.constant"), 1.0f);
    glUniform1f(glGetUniformLocation(shaderProgram, "spotlight.linear"), 0.0f);
    glUniform1f(glGetUniformLocation(shaderProgram, "spotlight.quadratic"), 0.0f);

    // Spotlight material properties
    glUniform1f(glGetUniformLocation(shaderProgram, "material.ra"), spotlight->getMaterial()->getRa());
    glUniform1f(glGetUniformLocation(shaderProgram, "material.rd"), spotlight->getMaterial()->getRd());
    glUniform1f(glGetUniformLocation(shaderProgram, "material.rs"), spotlight->getMaterial()->getRs());
}

void Shader::updatePointLightUniforms() {
    glm::vec3 lightPosition = light->getPosition();
    glm::vec4 lightColor = light->getColor();
    glm::vec4 lightPosition4 = glm::vec4(lightPosition, 1.0f);

    glUniform4fv(glGetUniformLocation(shaderProgram, "lights[0].position"), 1, glm::value_ptr(lightPosition4));
    glUniform4fv(glGetUniformLocation(shaderProgram, "lights[0].color"), 1, glm::value_ptr(lightColor));
    glUniform1f(glGetUniformLocation(shaderProgram, "lights[0].intensity"), 1.0f);
    glUniform1f(glGetUniformLocation(shaderProgram, "lights[0].ambientStrength"), 0.1f);
}

void Shader::updateDirectionalLightUniforms(DirectionalLight* directional) {
    glUniform3fv(glGetUniformLocation(shaderProgram, "dirLight.direction"), 1, glm::value_ptr(directional->getDirection()));
    glUniform4fv(glGetUniformLocation(shaderProgram, "dirLight.color"), 1, glm::value_ptr(directional->getColor()));
}

void Shader::use() {
    glUseProgram(shaderProgram);
}

[[depreacted("Should set an object color through Light")]]
void Shader::setUniformColor(float r, float g, float b, float a) {
    GLint colorLocation = glGetUniformLocation(shaderProgram, "fragColor");
    glUniform4f(colorLocation, r, g, b, a);
}

void Shader::setUniformMatrix(const glm::mat4& modelMatrix) {
    GLint modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));
    GLint normalMatrixLoc = glGetUniformLocation(shaderProgram, "normalMatrix");
    glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
}
