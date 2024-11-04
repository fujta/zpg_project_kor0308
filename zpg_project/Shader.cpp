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

    glm::vec3 lightPosition = light->getPosition();
    glm::vec4 lightColor = light->getColor();
    glm::vec3 viewPosition = camera->getPosition();
    glm::vec4 objectColor = light->getObjectColor();
    float shininess = light->getShininess();

	cout << shininess << endl;

    glUniform3fv(glGetUniformLocation(shaderProgram, "lightPosition"), 1, glm::value_ptr(lightPosition));
    glUniform4fv(glGetUniformLocation(shaderProgram, "lightColor"), 1, glm::value_ptr(lightColor));
    glUniform3fv(glGetUniformLocation(shaderProgram, "viewPosition"), 1, glm::value_ptr(viewPosition));
    glUniform4fv(glGetUniformLocation(shaderProgram, "objectColor"), 1, glm::value_ptr(objectColor));
    glUniform1f(glGetUniformLocation(shaderProgram, "shininess"), shininess);
    glUniform1i(glGetUniformLocation(shaderProgram, "numberOfLights"), 1);

    glm::vec4 lightPosition4 = glm::vec4(lightPosition, 1.0f);
    glUniform4fv(glGetUniformLocation(shaderProgram, "lights[0].position"), 1, glm::value_ptr(lightPosition4));
    glUniform4fv(glGetUniformLocation(shaderProgram, "lights[0].color"), 1, glm::value_ptr(lightColor));
    glUniform1f(glGetUniformLocation(shaderProgram, "lights[0].intensity"), 1.0f);
    glUniform1f(glGetUniformLocation(shaderProgram, "lights[0].ambientStrength"), 0.1f);
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
