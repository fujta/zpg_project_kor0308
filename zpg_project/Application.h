#ifndef APPLICATION_H
#define APPLICATION_H

#include "Model.h"
#include "Scene.h"

#include <GLFW/glfw3.h>
#include <vector>

#include "CameraMovementEnum.h"

class Application {
private:
    GLFWwindow* window;

    std::vector<Scene*> scenes;
    int currentSceneIndex;

    static Application* instance;

    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

    void changeSceneOnUserInteraction();
    void userActions(float deltaTime);

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
