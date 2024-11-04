#ifndef APPLICATION_H
#define APPLICATION_H

#include "Model.h"
#include "Scene.h"

#include <GLFW/glfw3.h>
#include <vector>

#include "CameraMovementEnum.h"
#include "SceneFactory.h"
#include "UserInputController.h"

#define DEFAULT_SCENE_INDEX 0
#define DEFAULT_VIEWPORT_HEIGHT 600
#define DEFAULT_VIEWPORT_WIDTH 800

#define NUMBER_OF_SCENES 4

class Application {
private:
    GLFWwindow* window;

    std::vector<Scene*> scenes;
    int currentSceneIndex;

    static Application* instance;
	UserInputController* userInputController;

    static void onMouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

    float lastX;
    float lastY;
    bool firstMouse;

    float deltaTime;
    float lastFrame;

public:
    Application();
    ~Application();

    void initialization();
    void createScenes();
    void run();

    static Application* getInstance();
};

#endif // APPLICATION_H
