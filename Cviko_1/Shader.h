#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>



class Shader
{
public:
	Shader();

	void Init(const char* vertex_shader_str, const char* fragment_shader_str);
	
	GLuint GetShader_prg();

private:
	GLuint vertexShader, fragmentShader, shaderProgram;

};

