#pragma once
#include <iostream>
#include <GL/glew.h>
#include <SOIL.h>

class Texture
{
public:
	Texture(const char* texture_path, GLenum textureType = GL_TEXTURE_2D);
	Texture(const char* x1, const char* x2,
		const char* y1, const char* y2,
		const char* z1, const char* z2,
		GLenum textureType = GL_TEXTURE_2D);
	void Bind();
	void Unbind();
	~Texture();
	int getTextureID();

private:
	GLenum type;
	GLuint textureID;
};

