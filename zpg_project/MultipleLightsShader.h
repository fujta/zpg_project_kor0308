#pragma once
#include "Shader.h"

/**
* @class MultipleLightsShader
* @brief Class for multiple lights shader
* @details This class is a subclass of Shader class. It is used to create a shader program that can handle multiple lights.
*
* @see Shader
*/
class MultipleLightsShader : public Shader
{
private:
	std::vector<Light*> lights;
	int numberOfLights;

public:
	MultipleLightsShader(Camera* camera, std::vector<Light*> lights, const string& vertexShaderPath, const string& fragmentShaderPath);
	~MultipleLightsShader();

	void addLight(Light* light);

	void onLightUpdated() override;
};

