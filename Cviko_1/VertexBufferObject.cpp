#include "VertexBufferObject.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>


VertexBufferObject::VertexBufferObject() {}

void VertexBufferObject::Init(float* points, size_t size)
{
	type_model = 0; //array of float points 
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	int help = size * sizeof(float);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), points, GL_STATIC_DRAW);
}

void VertexBufferObject::Init(Vertex* points, size_t size)
{
	type_model = 1; //Vertex struct array
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(Vertex), points, GL_STATIC_DRAW);
}


GLuint VertexBufferObject::GetVBO()
{
	return VBO;
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &VBO);
}


