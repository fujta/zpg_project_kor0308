#include "Scene.h"

Scene::Scene(float aspectRatio) {
    camera = new Camera(aspectRatio);
}

Scene::~Scene() {
    delete camera;

    for (auto obj : drawableObjects) {
        delete obj;
    }
}

Camera* Scene::getCamera() {
    return camera;
}

void Scene::render() {
    glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    for (auto drawableObject : drawableObjects) {
        if (!drawableObject->isSkybox()) {
            drawableObject->render();
        }
    }

    // Render skybox
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);

    for (auto drawableObject : drawableObjects) {
        if (drawableObject->isSkybox()) {
            drawableObject->render();
        }
    }

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
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

void Scene::addAnimation(Animation* animation) {
	animations.push_back(animation);
}

void Scene::updateAnimationFrame() {
	for (auto animation : animations) {
		animation->update();
	}
}
