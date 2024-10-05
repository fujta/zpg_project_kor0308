#include "Application.h"
#include <iostream>

Application::Application() : window(nullptr), shader(nullptr), model(nullptr) {}

Application::~Application() {
    if (window) glfwDestroyWindow(window);
    glfwTerminate();
    delete shader;
    delete model;
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
    shader = new Shader();
    const char* vertex_shader = "#version 330\nlayout(location=0) in vec3 vp;void main () { gl_Position = vec4(vp, 1.0);}";
    const char* fragment_shader = "#version 330\nout vec4 frag_colour;void main () { frag_colour = vec4(0.5, 0.0, 0.5, 1.0);}";
    shader->loadShaders(vertex_shader, fragment_shader);
}

void Application::createModels() {
    float points[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f
    };
    model = new Model(points, 9); // 9 = 3 vertices, 3 coordinates each
}

void Application::run() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();
        model->render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
