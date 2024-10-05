#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader {
private:
    GLuint shaderProgram; // Not accessible from outside

    GLuint compileShader(const char* source, GLenum type);

public:
    Shader();
    ~Shader();
    void loadShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
    void use();
};

#endif
