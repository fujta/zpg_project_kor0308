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
    for (auto drawableObject : drawableObjects) {
        if (drawableObject->isSkybox()) {
            glDisable(GL_DEPTH_TEST);
            drawableObject->render();
            glEnable(GL_DEPTH_TEST);
        }
    }

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    for (auto drawableObject : drawableObjects) {
        if (!drawableObject->isSkybox()) {
            glStencilFunc(GL_ALWAYS, drawableObject->getId(), 0xFF);

            drawableObject->render();
        }
    }

    glDisable(GL_STENCIL_TEST);
}


void Scene::addDrawableObject(DrawableObject* drawableObject)
{
    drawableObjects.push_back(drawableObject);
}

std::vector<DrawableObject*>& Scene::getDrawableObjects() {
	return drawableObjects;
}

std::vector<Animation*>& Scene::getAnimations()
{
	return animations;
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
