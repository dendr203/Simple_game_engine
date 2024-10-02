#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "VertexBufferObject.h"

class VertexArrayObject
{
public:
	VertexArrayObject();
	~VertexArrayObject();

	void Init(int num_of_edges, VertexBufferObject& VBO);

	GLuint GetVAO();

private:
	GLuint VAO;
};

