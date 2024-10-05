#ifndef APPLICATION_H
#define APPLICATION_H

#include "Shader.h"
#include "Model.h"
#include <GLFW/glfw3.h>

class Application {
private:
    GLFWwindow* window;
    Shader* shader;
    Model* model;

public:
    Application();
    ~Application();
    void initialization();
    void createShaders();
    void createModels();
    void run();
};

#endif
