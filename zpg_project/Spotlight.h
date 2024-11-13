#pragma once
#include "Light.h"
#include "Camera.h"
#include "ICameraObserver.h"

class Spotlight : public Light, public ICameraObserver {
public:
    Spotlight(Camera* camera = nullptr);
    ~Spotlight();

    void setDirection(const glm::vec3& direction);
    void setCutOff(float cutOff);
    void setOuterCutOff(float outerCutOff);

    glm::vec3& getDirection();
    float getCutOff();
    float getOuterCutOff();

    std::string getFragmentShaderName() override;

	void onCameraUpdated() override;

private:
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;
	Camera* camera;
};
