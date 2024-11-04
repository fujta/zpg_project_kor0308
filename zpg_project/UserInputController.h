#pragma once
#include  <iostream>
#include <GLFW/glfw3.h>
#include "Camera.h"

class UserInputController
{
public:
	void handleCameraMovement(GLFWwindow* window, float deltaTime, Camera* camera);
	void handleSceneChange(GLFWwindow* window, int& currentSceneIndex);
};

