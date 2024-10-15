#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "Shader.h"



class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	void init_shader(const char* vertex_shader_str, const char* fragment_shader_str);
	void use_shader();
	GLuint GetShader();

private:
	GLuint shaderProgram_id;
};

