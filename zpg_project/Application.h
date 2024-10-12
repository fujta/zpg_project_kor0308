#ifndef APPLICATION_H
#define APPLICATION_H

#include "Model.h"
#include "Scene.h"

#include <GLFW/glfw3.h>
#include <vector>

class Application {
private:
    GLFWwindow* window;

    std::vector<Scene*> scenes;
    int currentSceneIndex;

    void changeSceneOnUserInteraction();
    void userActionTransformations(DrawableObject* drawableObject);
    
public:
    Application();
    ~Application();

    void initialization();
    void createScenes();
    void run();
};

#endif
