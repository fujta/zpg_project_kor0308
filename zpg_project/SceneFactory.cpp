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
    treeObject->createShaders("baseVertexShader.glsl", "redColorFragmentShader.glsl", scene1->getCamera());
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

	DrawableObject* sphereObject1 = new DrawableObject(ShapeType::SPHERE);
    sphereObject1->createShaders("baseVertexShader.glsl", "baseFragmentShader.glsl", scene3->getCamera());
    sphereObject1->createModel();
	sphereObject1->setTransform()
		.addTransformation(new Translate(glm::vec3(2.0f, 0.0f, 0.0f)))
		.addTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
	scene3->addDrawableObject(sphereObject1);

    DrawableObject* sphereObject2 = new DrawableObject(ShapeType::SPHERE);
    sphereObject2->createShaders("baseVertexShader.glsl", "baseFragmentShader.glsl", scene3->getCamera());
    sphereObject2->createModel();
    sphereObject2->setTransform()
        .addTransformation(new Translate(glm::vec3(2.0f, 0.0f, 2.0f)))
        .addTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
    scene3->addDrawableObject(sphereObject2);

    DrawableObject* sphereObject3 = new DrawableObject(ShapeType::SPHERE);
    sphereObject3->createShaders("baseVertexShader.glsl", "baseFragmentShader.glsl", scene3->getCamera());
    sphereObject3->createModel();
    sphereObject3->setTransform()
        .addTransformation(new Translate(glm::vec3(0.0f, 0.0f, 2.0f)))
        .addTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
    scene3->addDrawableObject(sphereObject3);

    DrawableObject* sphereObject4 = new DrawableObject(ShapeType::SPHERE);
    sphereObject4->createShaders("baseVertexShader.glsl", "baseFragmentShader.glsl", scene3->getCamera());
    sphereObject4->createModel();
    sphereObject4->setTransform()
        .addTransformation(new Translate(glm::vec3(0.0f, 0.0f, 0.0f)))
        .addTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
    scene3->addDrawableObject(sphereObject4);


	return scene3;  
}
