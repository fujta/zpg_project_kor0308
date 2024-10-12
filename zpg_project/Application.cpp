#include "Application.h"
#include "ModelFactory.h"
#include "ShaderFactory.h"
#include "NumberGenerator.h"
#include <iostream>

Application::Application() : window(nullptr) {}

Application::~Application() {
    if (window) glfwDestroyWindow(window);
    glfwTerminate();
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

void Application::run() {
    glEnable(GL_DEPTH_TEST);//Do depth comparisons and update the depth buffer.
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->changeSceneOnUserInteraction();
        this->userActionTransformations(scenes[currentSceneIndex]->getDrawableObject(0));
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
}

void Application::userActionTransformations(DrawableObject* drawableObject) {
	glm::vec3 previousPosition = drawableObject->getTransform().getPosition();
    float previousRotationAngle = drawableObject->getTransform().getRotationAngle();

    float rotationSpeed = 1.0f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		drawableObject->getTransform().setPosition(previousPosition + glm::vec3(0.0f, 0.01f, 0.0f));
		std::cout << "W key pressed\n";
	}
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		drawableObject->getTransform().setPosition(previousPosition + glm::vec3(0.01f, 0.0f, 0.0f));
		std::cout << "D key pressed\n";
	}
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		drawableObject->getTransform().setPosition(previousPosition + glm::vec3(0.0f, -0.01f, 0.0f));
		std::cout << "S key pressed\n";
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		drawableObject->getTransform().setPosition(previousPosition + glm::vec3(-0.01f, 0.0f, 0.0f));
		std::cout << "A key pressed\n";
	}
    else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        drawableObject->getTransform().rotate(rotationSpeed, glm::vec3(1.0f, 0.9f, 0.0f));
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        drawableObject->getTransform().rotate(-rotationSpeed, glm::vec3(1.0f, 0.9f, 0.0f));
    }
}

void Application::createScenes() {
	// First Scene - Single bush and tree
    Scene* scene1 = new Scene();
    scenes.push_back(scene1);

    // Create multiple objects
    DrawableObject* bushObject = new DrawableObject(ShapeType::BUSH);
    bushObject->createShaders("baseVertexShader.glsl", "baseFragmentShader.glsl");
    bushObject->createModel();

    // Set transformations
    bushObject->getTransform().setPosition(glm::vec3(0.5f, 0.0f, 0.0f));
	bushObject->getTransform().setRotation(45.0f, glm::vec3(1.0f, 0.9f, 0.0f));
    bushObject->getTransform().setScale(glm::vec3(1.5f));
    scene1->addDrawableObject(bushObject);

    DrawableObject* treeObject = new DrawableObject(ShapeType::TREE);
    treeObject->createShaders("baseVertexShader.glsl", "redColorFragmentShader.glsl");
    treeObject->createModel();
    treeObject->getTransform().setPosition(glm::vec3(-0.5f, -0.5f, 0.0f));
    treeObject->getTransform().setScale(glm::vec3(0.19f));
    scene1->addDrawableObject(treeObject);

    // Second Scene - Forest
    Scene* scene2 = new Scene();
    scenes.push_back(scene2);

    int numTrees = 10;
    for (int i = 0; i < numTrees; ++i) {
        DrawableObject* treeObject = new DrawableObject(ShapeType::TREE);
        treeObject->createShaders("baseVertexShader.glsl", "baseFragmentShader.glsl");
        treeObject->createModel();

        // Random transformations
        glm::vec3 position = glm::vec3(NumberGenerator::randomFloat(-1.0f, 1.0f), -0.5f, NumberGenerator::randomFloat(-1.0f, 1.0f));
        float rotationAngle = NumberGenerator::randomFloat(0.0f, 360.0f);
        float scaleValue = NumberGenerator::randomFloat(0.01f, 0.19f);

        treeObject->getTransform().setPosition(position);
        treeObject->getTransform().setRotation(rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
        treeObject->getTransform().setScale(glm::vec3(scaleValue));

        scene2->addDrawableObject(treeObject);
    }

    int numBushes = 10;
    for (int i = 0; i < numBushes; ++i) {
        DrawableObject* bushObject = new DrawableObject(ShapeType::BUSH);
        bushObject->createShaders("baseVertexShader.glsl", "baseFragmentShader.glsl");
        bushObject->createModel();

        // Random transformations
        glm::vec3 position = glm::vec3(NumberGenerator::randomFloat(-1.0f, 1.0f), -0.8f, NumberGenerator::randomFloat(-1.0f, 1.0f));
        float rotationAngle = NumberGenerator::randomFloat(0.0f, 360.0f);
        float scaleValue = NumberGenerator::randomFloat(0.1f, 0.5f);

        bushObject->getTransform().setPosition(position);
        bushObject->getTransform().setRotation(rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
        bushObject->getTransform().setScale(glm::vec3(scaleValue));

        scene2->addDrawableObject(bushObject);
    }

    currentSceneIndex = 0;
}
