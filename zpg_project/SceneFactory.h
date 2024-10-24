#pragma once

#include "Scene.h"
#include "DrawableObject.h"
#include "NumberGenerator.h"

#include "Scale.h"
#include "Translate.h"
#include "Rotate.h"

#include "Light.h"

class SceneFactory
{
public:
	SceneFactory();
	~SceneFactory();

	static Scene* createBaseScene();
	static Scene* createForestScene();
	static Scene* createLightScene();
};

