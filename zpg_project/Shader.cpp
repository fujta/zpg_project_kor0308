#include "Shader.h"
#include <iostream>

Shader::Shader(Camera* camera) {
    shaderProgram = 0;
    this->camera = camera;
    camera->addObserver(this);
}

Shader::~Shader() {
    if (shaderProgram != 0) {
        glDeleteProgram(shaderProgram);
    }
    camera->removeObserver(this);
}

void Shader::onCameraUpdated() {
    this->use();
    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = camera->getProjectionMatrix();
    glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Shader::setUniformMatrix(const std::string& name, const glm::mat4& matrix) {
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    if (location == -1) {
        std::cerr << "Uniform " << name << " not found." << std::endl;
    }
    else {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
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

    viewMatrixLoc = glGetUniformLocation(shaderProgram, "viewMatrix");
    projectionMatrixLoc = glGetUniformLocation(shaderProgram, "projectionMatrix");

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

    onCameraUpdated();
}

void Shader::use() {
    glUseProgram(shaderProgram);
}

void Shader::setUniformColor(float r, float g, float b, float a) {
    GLint colorLocation = glGetUniformLocation(shaderProgram, "fragColor");
    glUniform4f(colorLocation, r, g, b, a);
}

void Shader::setUniformLocation(const glm::mat4& modelMatrix) {
    GLint modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}
