#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "VertexBufferObject.h"
#include "VertexArrayObject.h"

class Model
{
public:
	virtual void Init(const char* vertex_shader, const char* fragment_shader);

	virtual GLuint GetShader();
	virtual GLuint GetVAO();
	virtual GLuint GetVBO();
	
protected:
	 Shader shader;
	 VertexBufferObject VBO;
	 VertexArrayObject VAO;
	 
};


