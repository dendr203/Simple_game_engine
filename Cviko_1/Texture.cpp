#include "Texture.h"

Texture::Texture(const char* texture_path, GLenum textureType) : type(textureType)
{
	glActiveTexture(GL_TEXTURE0);
	textureID = SOIL_load_OGL_texture(texture_path, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (textureID == NULL)
	{
		printf("An error occurred while loading texture.\n");
		exit(EXIT_FAILURE);
	}
	glBindTexture(type, textureID);

	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Texture::Texture(const char* x1, const char* x2,
	const char* y1, const char* y2,
	const char* z1, const char* z2,
	GLenum textureType) : type(textureType)
{
	glActiveTexture(GL_TEXTURE0);
	textureID = SOIL_load_OGL_cubemap(x1, x2, y1, y2, z1, z2, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	if (textureID == NULL)
	{
		printf("An error occurred while loading texture.\n");
		exit(EXIT_FAILURE);
	}
	glBindTexture(type, textureID);

	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Texture::Bind()
{
	glBindTexture(type, textureID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

Texture::~Texture() {
	glDeleteTextures(1, &textureID);
}

int Texture::getTextureID()
{
	return textureID;
}