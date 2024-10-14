#pragma once
#include "Shader.h"
#include <string>

using namespace std;

class ShaderFactory
{
public:
    static Shader* createShader(const string& vertexShaderPath, const string& fragmentShaderPath, Camera* camera);
private:
    static string readShaderFromFile(const string& path);
};
