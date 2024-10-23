#include "Application.h"
#include "ModelFactory.h"
#include "ShaderFactory.h"
#include "NumberGenerator.h"
#include <iostream>

Application* Application::instance = nullptr;

Application::Application() : window(nullptr), currentSceneIndex(0), lastX(400), lastY(300), firstMouse(true), deltaTime(0.0f), lastFrame(0.0f) {
    instance = this;
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

    window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, 800, 600);

    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Application::run() {
    glEnable(GL_DEPTH_TEST); // Do depth comparisons and update the depth buffer.
    while (!glfwWindowShouldClose(window)) {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->changeSceneOnUserInteraction();
        this->userActions(deltaTime);

        scenes[currentSceneIndex]->render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Application::changeSceneOnUserInteraction() {
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

void Application::userActions(float deltaTime) {
    Camera* camera = scenes[currentSceneIndex]->getCamera();
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

void Application::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    Application* app = Application::getInstance();
    Camera* camera = app->scenes[app->currentSceneIndex]->getCamera();

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
	scenes.push_back(SceneFactory::createLightScene());

    currentSceneIndex = 0;
}
