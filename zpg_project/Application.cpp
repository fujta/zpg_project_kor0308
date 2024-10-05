#include "Application.h"
#include "ModelFactory.h"
#include "ShaderFactory.h"
#include <iostream>

Application::Application() : window(nullptr), shader(nullptr), model(nullptr), squareModel(nullptr) {}

Application::~Application() {
    if (window) glfwDestroyWindow(window);
    glfwTerminate();
    delete shader;
    delete model;
    delete squareModel;
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
}

void Application::createShaders() {
    shader = ShaderFactory::createShader("baseVertexShader.glsl", "baseFragmentShader.glsl");
    squareShader = ShaderFactory::createShader("baseVertexShader.glsl", "redColorFragmentShader.glsl");
}

void Application::createModels() {
    model = ModelFactory::createModel(ShapeType::TRIANGLE, glm::vec3(0.0f, 0.0f, 0.0f));
    squareModel = ModelFactory::createModel(ShapeType::SQUARE, glm::vec3(0.5f, 0.5f, 0.0f));
}

void Application::run() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();

        shader->setUniformColor(0.5f, 1.5f, 0.5f, 1.0f);
        model->render(ShapeType::TRIANGLE);

        squareShader->use();
        squareModel->render(ShapeType::SQUARE);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
