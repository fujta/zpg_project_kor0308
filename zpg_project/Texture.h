#pragma once
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <SOIL.h>

class Texture
{
public:
    Texture(const std::string& texturePath);
    ~Texture();

    void load();
    void bind(GLenum textureUnit = GL_TEXTURE0) const;
    void unbind() const;

    GLuint getTextureID() const;

private:
	std::string texturePath;
	GLuint textureID;
    GLuint textureUnit;
};

