#include "Texture.h"

Texture::Texture(const char* texture_path, GLenum textureUnit) : unit(textureUnit)
{
	glGenTextures(1, &textureID);
	glActiveTexture(unit);
	textureID = SOIL_load_OGL_texture(texture_path, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (textureID == NULL)
	{
		printf("An error occurred while loading texture.\n");
		exit(EXIT_FAILURE);
	}
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Texture::Texture(const char* x1, const char* x2,
	const char* y1, const char* y2,
	const char* z1, const char* z2,
	GLenum textureUnit) : unit(textureUnit)
{
	glGenTextures(1, &textureID);
	glActiveTexture(unit);
	textureID = SOIL_load_OGL_cubemap(x1, x2, y1, y2, z1, z2, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	if (textureID == NULL)
	{
		printf("An error occurred while loading texture.\n");
		exit(EXIT_FAILURE);
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}


Texture::~Texture() {
	glDeleteTextures(1, &textureID);
}

int Texture::getUnitID()
{
	int textureUnitIndex = unit - GL_TEXTURE0;
	return textureUnitIndex;
}