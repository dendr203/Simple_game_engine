#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>



class Shader
{
public:
	Shader();

	void init_shader(GLenum type, const char* shader_string);

	GLuint GetShader();
private:
	GLuint shader_id;

};

