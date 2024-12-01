#pragma once
#include "Scene.h"
#include "DrawableObject.h"
#include "Skybox.h"
#include "NumberGenerator.h"

#include "Scale.h"
#include "Translate.h"
#include "Rotate.h"
#include "RotateAnimation.h"
#include "TranslateAnimation.h"

#include "Light.h"
#include "ConstantLight.h"
#include "LambertLight.h"
#include "PhongLight.h"
#include "BlinnLight.h"
#include "Spotlight.h"
#include "DirectionalLight.h"

class SceneFactory
{
public:
	SceneFactory();
	~SceneFactory();

	static Scene* createBaseScene();
	static Scene* createForestScene();
	static Scene* createDarkForestScene();
	static Scene* createLightScene();
	static Scene* createLightDemonstrateScene();
};

