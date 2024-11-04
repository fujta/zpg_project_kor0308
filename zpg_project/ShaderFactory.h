#pragma once
#include "Shader.h"
#include "MultipleLightsShader.h"
#include <string>

using namespace std;

class ShaderFactory
{
public:
    static Shader* createShader(const string& vertexShaderPath, const string& fragmentShaderPath, Camera* camera, Light* light = nullptr);
    static Shader* createShader(const string& vertexShaderPath, const string& fragmentShaderPath, Camera* camera, std::vector<Light*> lights);
};
