#pragma once
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <SOIL.h>
#include <glm/glm.hpp>

class Texture
{
public:
	Texture(std::string texturePath);
	~Texture();

	void load();
	void bind();
	void unbind();

private:
	std::string texturePath;
	GLuint textureID;
};

