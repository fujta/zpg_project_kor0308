#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderLoader.h"
#include "Camera.h"
#include "Light.h"
#include "ICameraObserver.h"
#include "ILightObserver.h"

#include "Spotlight.h"
#include "DirectionalLight.h"

class Shader : public ICameraObserver, public ILightObserver {
protected:
    GLuint shaderProgram; // Must not be accessible from outside
    ShaderLoader* shaderLoader;
    GLint viewMatrixLoc;
    GLint projectionMatrixLoc;
    Camera* camera;

private: 
    Light* light;

	void updateCommonLightUniforms();
    void updateMaterialUniforms();
    void updatePointLightUniforms();
    void updateSpotlightUniforms(Spotlight* spotlight);
    void updateDirectionalLightUniforms(DirectionalLight* directional);

public:
    Shader(Camera* camera, Light* light, const string& vertexShaderPath, const string& fragmentShaderPath);
    ~Shader();

    void setUniformColor(float r, float g, float b, float a);
    void setUniformMatrix(const glm::mat4& modelMatrix);
    void use();
	void unuse();

    void addLight(Light* light);
    void setCamera(Camera* camera);

    void onCameraUpdated() override;
    void onLightUpdated() override;
};

#endif // SHADER_H
