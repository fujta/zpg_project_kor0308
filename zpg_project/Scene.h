#pragma once

#include "DrawableObject.h"
#include "Shader.h"
#include "ShaderFactory.h"
#include <vector>

class Scene {
public:
    Scene();
    ~Scene();

    void addDrawableObject(DrawableObject* drawableObject);
    DrawableObject* getDrawableObject(int index);
    void render();

private:
    std::vector<DrawableObject*> drawableObjects;
};

