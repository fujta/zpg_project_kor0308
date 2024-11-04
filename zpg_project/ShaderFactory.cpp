#include <iostream>
#include <fstream>
#include <sstream>

#include "ShaderFactory.h"
using namespace std;

Shader* ShaderFactory::createShader(const string& vertexShaderPath, const string& fragmentShaderPath, Camera* camera, Light* light) {
    Shader* shader = new Shader(camera, light, vertexShaderPath, fragmentShaderPath);

    return shader;
}

Shader* ShaderFactory::createShader(const string& vertexShaderPath, const string& fragmentShaderPath, Camera* camera, std::vector<Light*> lights) {
    Shader* shader = new MultipleLightsShader(camera, lights, vertexShaderPath, fragmentShaderPath);

    return shader;
}

