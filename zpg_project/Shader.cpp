#include "Shader.h"
#include <iostream>

Shader::Shader() {
    shaderProgram = 0;
}

Shader::~Shader() {
    if (shaderProgram != 0) {
        glDeleteProgram(shaderProgram);
    }
}

GLuint Shader::compileShader(const char* source, GLenum type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
        std::cerr << "Shader compilation error: " << strInfoLog << std::endl;
        delete[] strInfoLog;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

void Shader::loadShaders(const char* vertexShaderSource, const char* fragmentShaderSource) {
    GLuint vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);

    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
        std::cerr << "Program linking error: " << strInfoLog << std::endl;
        delete[] strInfoLog;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() {
    glUseProgram(shaderProgram);
}

void Shader::setUniformColor(float r, float g, float b, float a) {
    GLint colorLocation = glGetUniformLocation(shaderProgram, "fragColor");
    glUniform4f(colorLocation, r, g, b, a);
}

void Shader::setUniformLocation() {
    //glm::mat4 M = glm::mat4(1.0f);

    //// Define myView to move the object 3 units away from the camera
    //float myView = 0;

    //// Apply transformations
    //M = glm::rotate(glm::mat4(1.0f), 0.78539816f, glm::vec3(0.0f, 1.0f, 0.0f));  // Rotate 45 degrees around the Y-axis
    //M = glm::rotate(M, 0.78539816f, glm::vec3(1.0f, 0.0f, 0.0f));  // Rotate 45 degrees around the X-axis
    //M = glm::translate(M, glm::vec3(0.0f, 0.0f, myView));  // Move the object 3 units away from the camera
    //M = glm::scale(M, glm::vec3(0.5f));  // Scale the object down to 50% of its size

    glm::mat4 M = glm::mat4(1.0f);

    GLint modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(M));
}
