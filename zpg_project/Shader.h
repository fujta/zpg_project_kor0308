#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>                      // For basic GLM types like vec3 and mat4
#include <glm/gtc/matrix_transform.hpp>      // For matrix transformations like rotate, translate, scale


class Shader {
private:
    GLuint shaderProgram; // Must not be accessible from outside

    GLuint compileShader(const char* source, GLenum type);

public:
    Shader();
    ~Shader();
    void loadShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
    void setUniformColor(float r, float g, float b, float a);
    void setUniformLocation();
    void use();
};

#endif
