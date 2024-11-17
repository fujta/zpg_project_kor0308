#include "UserInputController.h"

void UserInputController::handleCameraMovement(GLFWwindow* window, float deltaTime, Camera* camera)
{
	static bool isCursorDisabled = false;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (!isCursorDisabled) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			isCursorDisabled = true;
		}
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
		if (isCursorDisabled) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			isCursorDisabled = false;
		}
	}

	float cameraSpeed = 1.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera->processKeyboard(FORWARD, cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera->processKeyboard(BACKWARD, cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera->processKeyboard(LEFT, cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera->processKeyboard(RIGHT, cameraSpeed);
	}	
}

void UserInputController::handleSceneChange(GLFWwindow* window, int& currentSceneIndex)
{	
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		currentSceneIndex = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		currentSceneIndex = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		currentSceneIndex = 2;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		currentSceneIndex = 3;
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
		currentSceneIndex = 4;
	}
}
