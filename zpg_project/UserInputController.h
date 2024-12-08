#pragma once
#include "Application.h"
#include  <iostream>
#include <GLFW/glfw3.h>
#include "Camera.h"

class Application;

class UserInputController
{
public:
	void handleCameraMovement(GLFWwindow* window, float deltaTime, Camera* camera);
	void handleSceneChange(GLFWwindow* window, int& currentSceneIndex);
	void handleMouseClick(GLFWwindow* window, int currentSceneIndex);
};

