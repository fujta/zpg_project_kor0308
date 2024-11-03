#include "UserInputController.h"

void UserInputController::handleCameraMovement(GLFWwindow* window, float deltaTime, Camera* camera)
{
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
}
