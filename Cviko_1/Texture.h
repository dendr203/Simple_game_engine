#pragma once
#include <iostream>
#include <GL/glew.h>
#include <SOIL.h>

class Texture
{
public:
	Texture(const char* texture_path, GLenum textureUnit);
	Texture(const char* x1, const char* x2,
		const char* y1, const char* y2,
		const char* z1, const char* z2,
		GLenum textureUnit);

	~Texture();
	int getUnitID();

private:
	GLenum unit;
	GLuint textureID;
};

