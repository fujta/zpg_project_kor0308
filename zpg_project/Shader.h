#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Light.h"
#include "ICameraObserver.h"
#include "ILightObserver.h"

class Shader : public ICameraObserver, public ILightObserver {
private:
    GLuint shaderProgram; // Must not be accessible from outside
    Camera* camera;
    Light* light;

    GLint viewMatrixLoc;
    GLint projectionMatrixLoc;

    GLuint compileShader(const char* source, GLenum type);

public:
    Shader(Camera* camera, Light* light);
    ~Shader();
    void loadShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
    void setUniformColor(float r, float g, float b, float a);
    void setUniformLocation(const glm::mat4& modelMatrix);
    void setUniformMatrix(const std::string& name, const glm::mat4& matrix);
    void use();

    void onCameraUpdated() override;
    void onLightUpdated() override;
};

#endif // SHADER_H
