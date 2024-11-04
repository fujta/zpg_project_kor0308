#include "MultipleLightsShader.h"

MultipleLightsShader::MultipleLightsShader(Camera* camera, std::vector<Light*> lights, const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    : Shader(camera, nullptr, vertexShaderPath, fragmentShaderPath), numberOfLights(0)
{
    for (Light* light : lights) {
        addLight(light);
    }
}

MultipleLightsShader::~MultipleLightsShader() {
    for (Light* light : lights) {
        light->removeObserver(this);
    }
}

void MultipleLightsShader::addLight(Light* light) {
    lights.push_back(light);
    light->addObserver(this);
    numberOfLights++;
    onLightUpdated();
}

void MultipleLightsShader::onLightUpdated() {
    this->use();

    glUniform1i(glGetUniformLocation(shaderProgram, "numberOfLights"), numberOfLights);

    for (int i = 0; i < numberOfLights; ++i) {
        std::string positionName = "lights[" + std::to_string(i) + "].position";
        std::string colorName = "lights[" + std::to_string(i) + "].color";

        glm::vec4 lightPosition = glm::vec4(lights[i]->getPosition(), 1.0f);
        glUniform4fv(glGetUniformLocation(shaderProgram, positionName.c_str()), 1, glm::value_ptr(lightPosition));
        glUniform4fv(glGetUniformLocation(shaderProgram, colorName.c_str()), 1, glm::value_ptr(lights[i]->getColor()));
    }

    if (!lights.empty()) {
        glm::vec4 objectColor = lights[0]->getObjectColor();
        glUniform4fv(glGetUniformLocation(shaderProgram, "objectColor"), 1, glm::value_ptr(objectColor));

        float shininess = lights[0]->getShininess();
        glUniform1f(glGetUniformLocation(shaderProgram, "shininess"), shininess);
    }

    glm::vec3 viewPosition = camera->getPosition();
    glUniform3fv(glGetUniformLocation(shaderProgram, "viewPosition"), 1, glm::value_ptr(viewPosition));
}



