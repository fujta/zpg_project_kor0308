#pragma once

#include <vector>
#include "Animation.h"
#include "DrawableObject.h"
#include "Shader.h"
#include "ShaderFactory.h"
#include "Camera.h"

class Scene {
public:
    Scene(float aspectRatio);
    ~Scene();

    void addDrawableObject(DrawableObject* drawableObject);
    DrawableObject* getDrawableObject(int index);
    void render();

    Camera* getCamera();

    void addAnimation(Animation* animation);
    void updateAnimationFrame();

    std::vector<DrawableObject*>& getDrawableObjects();
    std::vector<Animation*>& getAnimations();

private:
    std::vector<DrawableObject*> drawableObjects;
    std::vector<Animation*> animations;

    Camera* camera;
};

