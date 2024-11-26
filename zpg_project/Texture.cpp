#include "Texture.h"

Texture::Texture(const std::string& texturePath) : textureID(0), texturePath(texturePath), textureUnit(0) {}

Texture::~Texture()
{
}

void Texture::load() {
    // Bind the texture before setting parameters
    glBindTexture(GL_TEXTURE_2D, this->textureID);

    // Load the texture using SOIL, which returns a texture ID with data already uploaded
    this->textureID = SOIL_load_OGL_texture(
        this->texturePath.c_str(),
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    // Check if the texture was loaded successfully
    if (this->textureID == 0) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
        throw std::runtime_error("Failed to load texture: " + texturePath);
        return;
    } 

    glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::bind(GLenum textureUnit) const {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getTextureID() const {
    return textureID;
}