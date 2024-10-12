#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {
	for (auto obj : drawableObjects) {
		delete obj;
	}
}

void Scene::render() {
	//shader->use();
	//shader->setUniformLocation();
	//model->render(ShapeType::TRIANGLE);

	//squareShader->use();
	//squareModel->render(ShapeType::SQUARE);

	for (auto drawableObject : drawableObjects) {
		drawableObject->render();
	}
}

void Scene::addDrawableObject(DrawableObject* drawableObject)
{
	drawableObjects.push_back(drawableObject);
}

DrawableObject* Scene::getDrawableObject(int index) {
	if (index >= 0 && index < drawableObjects.size()) {
		return drawableObjects[index];
	}
	return nullptr;
}
