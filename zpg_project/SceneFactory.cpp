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
    Light* lamberLight = new LambertLight();

    int numTrees = 50;
    for (int i = 0; i < numTrees; ++i) {

        DrawableObject* treeObject = new DrawableObject(ShapeType::TREE);
        treeObject->createShaders("lightVertexShader.glsl", lamberLight->getFragmentShaderName(), scene2->getCamera(), lamberLight);
        treeObject->createModel();

        float randX = NumberGenerator::randomFloat(-5.0f, 5.0f);
        float randY = NumberGenerator::randomFloat(-5.0f, 5.0f);
		float randScale = NumberGenerator::randomFloat(0.01f, 0.19f);
		float randRotate = NumberGenerator::randomFloat(0.0f, 0.80f);

        treeObject->setTransform()
            .addTransformation(new Translate(glm::vec3(randX, 0, randY)))
            .addTransformation(new Scale(glm::vec3(randScale, randScale, randScale)))
            .addTransformation(new Rotate(randRotate, glm::vec3(0, 1, 0)));

        scene2->addDrawableObject(treeObject);

        if (i == 20) {
            glm::vec3 minPos(-15.0f, 0.0f, -15.0f);
            glm::vec3 maxPos(15.0f, 0.0f, 15.0f);

            TranslateAnimation* translateAnim = new TranslateAnimation(treeObject, glm::vec3(0.1f, 0.0f, 0.1f), minPos, maxPos);
            scene2->addAnimation(translateAnim);
        }    
    }

    lamberLight->setPosition(glm::vec3(0.0f, 2.0f, 0.0f));
    lamberLight->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    lamberLight->setObjectColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    lamberLight->setShininess(1.0f);

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

	Light* phong = new PhongLight();
	Light* phongBludicka = new PhongLight();
	std::vector<Light*> lights;

	lights.push_back(phong);
	lights.push_back(phongBludicka);

	// Three trees to test multiple lights - bludièky
	DrawableObject* treeObject1 = new DrawableObject(ShapeType::TREE);
	treeObject1->createShaders("lightVertexShader.glsl", phong->getFragmentShaderName(), scene2->getCamera(), lights);
	treeObject1->createModel();
	treeObject1->setTransform()
		.addTransformation(new Translate(glm::vec3(0.0f, 0.0f, 0.0f)))
		.addTransformation(new Scale(glm::vec3(0.1f, 0.1f, 0.1f)));
	scene2->addDrawableObject(treeObject1);

    RotateAnimation* rotateAnim = new RotateAnimation(treeObject1, 0.5f, glm::vec3(0, 1, 0));
    scene2->addAnimation(rotateAnim);

	DrawableObject* treeObject2 = new DrawableObject(ShapeType::TREE);
	treeObject2->createShaders("lightVertexShader.glsl", phong->getFragmentShaderName(), scene2->getCamera(), lights);
	treeObject2->createModel();
	treeObject2->setTransform()
		.addTransformation(new Translate(glm::vec3(0.0f, 0.0f, 1.0f)))
		.addTransformation(new Scale(glm::vec3(0.1f, 0.1f, 0.1f)));
	scene2->addDrawableObject(treeObject2);

	DrawableObject* treeObject3 = new DrawableObject(ShapeType::TREE);
	treeObject3->createShaders("lightVertexShader.glsl", phong->getFragmentShaderName(), scene2->getCamera(), lights);
	treeObject3->createModel();
	treeObject3->setTransform()
		.addTransformation(new Translate(glm::vec3(1.0f, 0.0f, 0.0f)))
		.addTransformation(new Scale(glm::vec3(0.1f, 0.1f, 0.1f)));
	scene2->addDrawableObject(treeObject3);

	phong->setObjectColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	phong->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	phong->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	phong->setShininess(1.0f);

	return scene2;
}

Scene* SceneFactory::createLightScene() {
    // Third Scene - Light
    Scene* scene3 = new Scene(4.0f / 3.0f);

    Light* light = new PhongLight();
    Light* light2 = new PhongLight();
	string fragmentShaderName = light->getFragmentShaderName();

	std::vector<Light*> lights;
	lights.push_back(light);
	//lights.push_back(light2);

	// Create only one shader with light
    ShaderFactory factory;
    Shader* shader = factory.createShader("lightVertexShader.glsl", fragmentShaderName, scene3->getCamera(), lights);

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

    light->setPosition(glm::vec3(0.0f, -10.0f, 0.0f));
    light->setColor(glm::vec4(0.0f, 0.5f, 1.0f, 1.0f));
    light->setObjectColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    light2->setPosition(glm::vec3(0.0f, 10.0f, 0.0f));
    light2->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    return scene3;
}

Scene* SceneFactory::createLightDemonstrateScene() {
	// Fourth Scene - Light Demonstrate
	Scene* scene4 = new Scene(4.0f / 3.0f);

	Light* constantLight = new ConstantLight();
	Light* lamberLight = new LambertLight();
	Light* phongLight = new PhongLight();
	Light* blinLight = new BlinnLight();

	// Create and set sphereObject1
	DrawableObject* sphereObject1 = new DrawableObject(ShapeType::SPHERE);
	sphereObject1->createShaders("lightVertexShader.glsl", constantLight->getFragmentShaderName(), scene4->getCamera(), constantLight);
	sphereObject1->createModel();
    sphereObject1->setTransform()
        .addTransformation(new Translate(glm::vec3(2.0f, 0.0f, 0.0f)))
        .addTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
	scene4->addDrawableObject(sphereObject1);
    constantLight->setPosition(glm::vec3(0.0f, 10.0f, 5.0f));
    constantLight->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    constantLight->setObjectColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	// Create and set sphereObject2
	DrawableObject* sphereObject2 = new DrawableObject(ShapeType::SPHERE);
    sphereObject2->createShaders("lightVertexShader.glsl", lamberLight->getFragmentShaderName(), scene4->getCamera(), lamberLight);
	sphereObject2->createModel();
	sphereObject2->setTransform()
		.addTransformation(new Translate(glm::vec3(4.0f, 0.0f, 0.0f)))
        .addTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
	scene4->addDrawableObject(sphereObject2);
    lamberLight->setPosition(glm::vec3(3.0f, 1.0f, 3.0f));
    lamberLight->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    lamberLight->setObjectColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    lamberLight->setShininess(90.0f);

	// Create and set sphereObject3
	DrawableObject* sphereObject3 = new DrawableObject(ShapeType::SPHERE);
    sphereObject3->createShaders("lightVertexShader.glsl", phongLight->getFragmentShaderName(), scene4->getCamera(), phongLight);
	sphereObject3->createModel();
    sphereObject3->setTransform()
        .addTransformation(new Translate(glm::vec3(6.0f, 0.0f, 0.0f)))
        .addTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
	scene4->addDrawableObject(sphereObject3);
    phongLight->setPosition(glm::vec3(0.0f, 10.0f, 9.0f));
    phongLight->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    phongLight->setObjectColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    // Create and set sphereObject4
    DrawableObject* sphereObject4 = new DrawableObject(ShapeType::SPHERE);
    sphereObject4->createShaders("lightVertexShader.glsl", blinLight->getFragmentShaderName(), scene4->getCamera(), blinLight);
    sphereObject4->createModel();
    sphereObject4->setTransform()
        .addTransformation(new Translate(glm::vec3(8.0f, 0.0f, 0.0f)))
        .addTransformation(new Scale(glm::vec3(0.5f, 0.5f, 0.5f)));
    scene4->addDrawableObject(sphereObject4);
    blinLight->setPosition(glm::vec3(0.0f, 10.0f, 11.0f));
    blinLight->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    blinLight->setObjectColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	blinLight->setShininess(32.0f);

	return scene4;
}
