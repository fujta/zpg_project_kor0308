#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

class Shader {
private:
    GLuint shaderProgram; // Must not be accessible from outside

    GLuint compileShader(const char* source, GLenum type);

public:
    Shader();
    ~Shader();
    void loadShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
    void setUniformColor(float r, float g, float b, float a);
    void use();
};

#endif
