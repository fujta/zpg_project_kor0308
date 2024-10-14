#include <iostream>
#include <fstream>
#include <sstream>

#include "ShaderFactory.h"
using namespace std;

Shader* ShaderFactory::createShader(const string& vertexShaderPath, const string& fragmentShaderPath, Camera* camera) {
    string vertexShaderCode = readShaderFromFile(vertexShaderPath);
    string fragmentShaderCode = readShaderFromFile(fragmentShaderPath);

    if (vertexShaderCode.empty() || fragmentShaderCode.empty()) {
        return nullptr;
    }

    Shader* shader = new Shader(camera);
    shader->loadShaders(vertexShaderCode.c_str(), fragmentShaderCode.c_str());

    return shader;
}

string ShaderFactory::readShaderFromFile(const string& path) {
    ifstream file(path);

    if (!file.is_open()) {
        cerr << "Failed to open file: " << path << endl;
        return "";
    }

    stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}
