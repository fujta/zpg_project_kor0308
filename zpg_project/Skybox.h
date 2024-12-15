#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include "DrawableObject.h"
#include "Translate.h"

class Skybox : public DrawableObject, public ICameraObserver
{
public:
	Skybox(Camera* camera);
	~Skybox();

	void createShaders(Camera* camera, Light* light);
	void createModel();
	void onCameraUpdated() override;
	void setFollowCamera(bool followCamera);
	bool getFollowCamera();
private:
	Camera* camera;
	bool followCamera = true;
};

