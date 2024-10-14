#pragma once

#include "DrawableObject.h"
#include "Shader.h"
#include "ShaderFactory.h"
#include "Camera.h"
#include <vector>

class Scene {
public:
    Scene(float aspectRatio);
    ~Scene();

    void addDrawableObject(DrawableObject* drawableObject);
    DrawableObject* getDrawableObject(int index);
    void render();

    Camera* getCamera();

private:
    std::vector<DrawableObject*> drawableObjects;
    Camera* camera;
};

