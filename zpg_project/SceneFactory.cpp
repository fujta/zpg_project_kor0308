#include "SceneFactory.h"

SceneFactory::SceneFactory() {
}
SceneFactory::~SceneFactory() {
}

Scene* SceneFactory::createBaseScene() {
    // First Scene - Single bush and tree
    Scene* scene1 = new Scene(4.0f / 3.0f);

    // Create multiple objects
    DrawableObject* bushObject = new DrawableObject(ShapeType::BUSH);
    bushObject->createShaders("baseVertexShader.glsl", "baseFragmentShader.glsl", scene1->getCamera());
    bushObject->createModel();

    // Set transformations
    bushObject->setTransform()
        .addTransformation(new Translate(glm::vec3(1.0f, 1.0f, 0.0f)))
        .addTransformation(new Scale(glm::vec3(2.0f, 2.0f, 2.0f)))
        .addTransformation(new Rotate(90.0f, glm::vec3(0.5f, 0.5f, 0.5f)));
    scene1->addDrawableObject(bushObject);

    DrawableObject* treeObject = new DrawableObject(ShapeType::TREE);
    treeObject->createShaders("baseVertexShader.glsl", "baseFragmentShader.glsl", scene1->getCamera());
    treeObject->createModel();
    scene1->addDrawableObject(treeObject);

	return scene1;
}

Scene* SceneFactory::createForestScene() {
    // Second Scene - Forest
    Scene* scene2 = new Scene(4.0f / 3.0f);

    int numTrees = 50;
    for (int i = 0; i < numTrees; ++i) {
        DrawableObject* treeObject = new DrawableObject(ShapeType::TREE);
        treeObject->createShaders("baseVertexShader.glsl", "baseFragmentShader.glsl", scene2->getCamera());
        treeObject->createModel();

        float randX = NumberGenerator::randomFloat(-10.0f, 10.0f);
        float randY = NumberGenerator::randomFloat(-10.0f, 10.0f);
		float randScale = NumberGenerator::randomFloat(0.01f, 0.19f);
		float randRotate = NumberGenerator::randomFloat(0.0f, 0.80f);

        treeObject->setTransform()
            .addTransformation(new Translate(glm::vec3(randX, 0, randY)))
            .addTransformation(new Scale(glm::vec3(randScale, randScale, randScale)))
            .addTransformation(new Rotate(randRotate, glm::vec3(0, 1, 0)));

        scene2->addDrawableObject(treeObject);
    }

    int numBushes = 50;
    for (int i = 0; i < numBushes; ++i) {
        DrawableObject* bushObject = new DrawableObject(ShapeType::BUSH);
        bushObject->createShaders("baseVertexShader.glsl", "baseFragmentShader.glsl", scene2->getCamera());
        bushObject->createModel();

        float randX = NumberGenerator::randomFloat(-10.0f, 10.0f);
        float randY = NumberGenerator::randomFloat(-10.0f, 10.0f);
        float randScale = NumberGenerator::randomFloat(0.01f, 0.19f);
        float randRotate = NumberGenerator::randomFloat(0.0f, 0.80f);

        bushObject->setTransform()
            .addTransformation(new Translate(glm::vec3(randX, 0, randY)))
            .addTransformation(new Scale(glm::vec3(randScale, randScale, randScale)))
            .addTransformation(new Rotate(randRotate, glm::vec3(0, 1, 0)));

        scene2->addDrawableObject(bushObject);
    }

	return scene2;
}

Scene* SceneFactory::createLightScene() {
    // Third Scene - Light
    Scene* scene3 = new Scene(4.0f / 3.0f);

    Light* light = new Light();

	// Create only one shader with light
    ShaderFactory factory;
    Shader* shader = factory.createShader("lightVertexShader.glsl", "blinnPhongLightFragmentShader.glsl", scene3->getCamera(), light);

    if (!shader) {
        std::cerr << "Failed to create shader." << std::endl;
        return nullptr;
    }

	// Create and set sphereObject1
    DrawableObject* sphereObject1 = new DrawableObject(ShapeType::SPHERE);
    sphereObject1->createShaders(shader);
    sphereObject1->createModel();
    sphereObject1->setTransform()
        .addTransformation(new Translate(glm::vec3(2.0f, 0.0f, 0.0f)))
        .addTransformation(new Rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f)))
        .addTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
    scene3->addDrawableObject(sphereObject1);

	// Create and set sphereObject2
    DrawableObject* sphereObject2 = new DrawableObject(ShapeType::SPHERE);
    sphereObject2->createShaders(shader);
    sphereObject2->createModel();
    sphereObject2->setTransform()
        .addTransformation(new Translate(glm::vec3(2.0f, 0.0f, 2.0f)))
        .addTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
    scene3->addDrawableObject(sphereObject2);

	// Create and set sphereObject3
    DrawableObject* sphereObject3 = new DrawableObject(ShapeType::SPHERE);
    sphereObject3->createShaders(shader);
    sphereObject3->createModel();
    sphereObject3->setTransform()
        .addTransformation(new Translate(glm::vec3(0.0f, 0.0f, 2.0f)))
        .addTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
    scene3->addDrawableObject(sphereObject3);

	// Create and set sphereObject4
    DrawableObject* sphereObject4 = new DrawableObject(ShapeType::SPHERE);
    sphereObject4->createShaders(shader);
    sphereObject4->createModel();
    sphereObject4->setTransform()
        .addTransformation(new Translate(glm::vec3(0.0f, 0.0f, 0.0f)))
        .addTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
    scene3->addDrawableObject(sphereObject4);

    light->setPosition(glm::vec3(0.0f, 10.0f, 0.0f));
    light->setColor(glm::vec4(0.5f, 0.5f, 0.1f, 1.0f));

    return scene3;
}

Scene* SceneFactory::createLightDemonstrateScene() {
	// Fourth Scene - Light Demonstrate
	Scene* scene4 = new Scene(4.0f / 3.0f);

	Light* light1 = new Light();
	Light* light2 = new Light();
	Light* light3 = new Light();
	Light* light4 = new Light();

	// Create and set sphereObject1
	DrawableObject* sphereObject1 = new DrawableObject(ShapeType::SPHERE);
	sphereObject1->createShaders("lightVertexShader.glsl", "constantLightFragmentShader.glsl", scene4->getCamera(), light1);
	sphereObject1->createModel();
    sphereObject1->setTransform()
        .addTransformation(new Translate(glm::vec3(2.0f, 0.0f, 0.0f)))
        .addTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
	scene4->addDrawableObject(sphereObject1);
    light1->setPosition(glm::vec3(0.0f, 10.0f, 5.0f));
    light1->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	// Create and set sphereObject2
	DrawableObject* sphereObject2 = new DrawableObject(ShapeType::SPHERE);
    sphereObject2->createShaders("lightVertexShader.glsl", "lambertLightFragmentShader.glsl", scene4->getCamera(), light2);
	sphereObject2->createModel();
	sphereObject2->setTransform()
		.addTransformation(new Translate(glm::vec3(4.0f, 0.0f, 0.0f)))
        .addTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
	scene4->addDrawableObject(sphereObject2);
    light2->setPosition(glm::vec3(0.0f, 10.0f, 7.0f));
    light2->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	// Create and set sphereObject3
	DrawableObject* sphereObject3 = new DrawableObject(ShapeType::SPHERE);
    sphereObject3->createShaders("lightVertexShader.glsl", "phongLightFragmentShader.glsl", scene4->getCamera(), light3);
	sphereObject3->createModel();
    sphereObject3->setTransform()
        .addTransformation(new Translate(glm::vec3(6.0f, 0.0f, 0.0f)))
        .addTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
	scene4->addDrawableObject(sphereObject3);
    light3->setPosition(glm::vec3(0.0f, 10.0f, 9.0f));
    light3->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    // Create and set sphereObject4
    DrawableObject* sphereObject4 = new DrawableObject(ShapeType::SPHERE);
    sphereObject4->createShaders("lightVertexShader.glsl", "blinnPhongLightFragmentShader.glsl", scene4->getCamera(), light4);
    sphereObject4->createModel();
    sphereObject4->setTransform()
        .addTransformation(new Translate(glm::vec3(8.0f, 0.0f, 0.0f)))
        .addTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
    scene4->addDrawableObject(sphereObject4);
    light4->setPosition(glm::vec3(0.0f, 10.0f, 11.0f));
    light4->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	return scene4;
}
