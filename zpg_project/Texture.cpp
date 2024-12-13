#include "Texture.h"

Texture::Texture(const std::string& texturePath) : textureID(0), texturePath(texturePath), textureUnit(0) {}

Texture::~Texture()
{
    if (this->textureID) {
        glDeleteTextures(1, &this->textureID);
    }
}

bool Texture::isSkyboxTexture() const {
	return isSkybox;
}

void Texture::loadSkybox() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);

	this->textureID = SOIL_load_OGL_cubemap("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	if (this->textureID == 0) {
		std::cerr << "Failed to load skybox texture: " << texturePath << std::endl;
		throw std::runtime_error("Failed to load skybox texture: " + texturePath);

		return;
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	isSkybox = true;
}

void Texture::load() {
    this->textureID = SOIL_load_OGL_texture(
        this->texturePath.c_str(),
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
    );

    if (this->textureID == 0) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
        throw std::runtime_error("Failed to load texture: " + texturePath);
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    isSkybox = false;
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