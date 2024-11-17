#include "Application.h"
#include "ModelFactory.h"
#include "ShaderFactory.h"
#include "NumberGenerator.h"
#include <iostream>

Application* Application::instance = nullptr;

Application::Application() : window(nullptr), currentSceneIndex(0), lastX(400), lastY(300), firstMouse(true), deltaTime(0.0f), lastFrame(0.0f) {
    instance = this;
	userInputController = new UserInputController();
}

Application::~Application() {
    for (auto scene : scenes) {
        delete scene;
    }
    if (window) glfwDestroyWindow(window);
    glfwTerminate();
}

Application* Application::getInstance() {
    return instance;
}

void Application::initialization() {
    if (!glfwInit()) {
        std::cerr << "ERROR: could not start GLFW3\n";
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(DEFAULT_VIEWPORT_WIDTH, DEFAULT_VIEWPORT_HEIGHT, "ZPG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, DEFAULT_VIEWPORT_WIDTH, DEFAULT_VIEWPORT_HEIGHT);

    glfwSetCursorPosCallback(window, onMouseCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

void Application::run() {
    glEnable(GL_DEPTH_TEST); // Do depth comparisons and update the depth buffer.

    while (!glfwWindowShouldClose(window)) {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		userInputController->handleSceneChange(window, currentSceneIndex);
		userInputController->handleCameraMovement(window, deltaTime, scenes[currentSceneIndex]->getCamera());

		scenes[currentSceneIndex]->updateAnimationFrame();
        scenes[currentSceneIndex]->render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}


void Application::onMouseCallback(GLFWwindow* window, double xpos, double ypos) {
    Application* app = Application::getInstance();
    Camera* camera = app->scenes[app->currentSceneIndex]->getCamera();

    int cursorState = glfwGetInputMode(window, GLFW_CURSOR);
    if (cursorState == GLFW_CURSOR_NORMAL) {
        return;
    }

    if (app->firstMouse) {
        app->lastX = xpos;
        app->lastY = ypos;
        app->firstMouse = false;
    }

    float xoffset = xpos - app->lastX;
    float yoffset = app->lastY - ypos;

    app->lastX = xpos;
    app->lastY = ypos;

    camera->processMouseMovement(xoffset, yoffset);
}

void Application::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
 
    Application* app = Application::getInstance();
    app->scenes[app->currentSceneIndex]->getCamera()->setAspectRatio((float)width / (float)height);
}

void Application::createScenes() {
	scenes.push_back(SceneFactory::createBaseScene());
	scenes.push_back(SceneFactory::createForestScene());
	scenes.push_back(SceneFactory::createDarkForestScene());
	scenes.push_back(SceneFactory::createLightScene());
	scenes.push_back(SceneFactory::createLightDemonstrateScene());

    currentSceneIndex = DEFAULT_SCENE_INDEX;
}
