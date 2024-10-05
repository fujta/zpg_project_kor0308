#pragma once
#include "Shader.h"
#include <string>

using namespace std;

class ShaderFactory
{
public:
	static Shader* createShader(string vertexShaderPath, string fragmentShaderPath);
private:
	static string readShaderFromFile(const string path);
};