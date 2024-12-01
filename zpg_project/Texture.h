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
	void loadSkybox();
    void bind(GLenum textureUnit = GL_TEXTURE0) const;
    void unbind() const;

    GLuint getTextureID() const;

	bool isSkyboxTexture() const;

private:
	bool isSkybox;
	std::string texturePath;
	GLuint textureID;
    GLuint textureUnit;
};

