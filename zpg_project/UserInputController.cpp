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

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera->processKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera->processKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera->processKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera->processKeyboard(RIGHT, deltaTime);
	}
}

void UserInputController::handleMouseClick(GLFWwindow* window, int currentSceneIndex) {
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {

		Application* app = Application::getInstance();
		if (!app) return;

		Scene* currentScene = app->getScenes()[currentSceneIndex];
		if (!currentScene) return;

		Camera* camera = currentScene->getCamera();
		if (!camera) return;
		
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		double newY = height - ypos;
		float depth;
		glReadPixels((int)xpos, (int)newY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

		if (depth < 1.0f) {
			glm::mat4 view = camera->getViewMatrix();
			glm::mat4 projection = camera->getProjectionMatrix();
			glm::vec4 viewport = glm::vec4(0, 0, width, height);
			glm::vec3 screenPos = glm::vec3((float)xpos, (float)newY, depth);
			glm::vec3 worldPos = glm::unProject(screenPos, view, projection, viewport);

			LambertLight* lambertLight = new LambertLight();

			DrawableObject* treeObject = new DrawableObject(ShapeType::TREE);
			treeObject->createShaders("lightVertexShader.glsl", lambertLight->getFragmentShaderName(), currentScene->getCamera(), lambertLight);
			treeObject->createModel();

			treeObject->setTransform()
				.addTransformation(new Translate(worldPos))
				.addTransformation(new Scale(glm::vec3(0.1f, 0.1f, 0.1f)));
			currentScene->addDrawableObject(treeObject);

			lambertLight->setPosition(glm::vec3(0.0f, 2.0f, 0.0f));
			lambertLight->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			lambertLight->setObjectColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		}

		return;
	}


	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		Application* app = Application::getInstance();
		if (!app) return;

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		ypos = height - ypos;

		GLuint index;
		glReadPixels(static_cast<int>(xpos), static_cast<int>(ypos), 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		if (index > 0) {
			app->removeDrawableObjectById(static_cast<int>(index));
		}
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
