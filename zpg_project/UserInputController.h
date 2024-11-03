#pragma once
#include "Camera.h"
#include <GLFW/glfw3.h>

class UserInputController
{
public:
	void handleCameraMovement(GLFWwindow* window, float deltaTime, Camera* camera);
	void handleSceneChange(GLFWwindow* window, int& currentSceneIndex);
};

