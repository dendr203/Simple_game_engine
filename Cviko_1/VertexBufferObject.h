#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	float position[4];  // 4 hodnoty pro pozici
	float color[4];     // 4 hodnoty pro barvu
} Vertex;


class VertexBufferObject
{
public:
	VertexBufferObject();

	void Init(float* points, size_t size);
	void Init(Vertex* points, size_t size);

	~VertexBufferObject();

	GLuint GetVBO();


private:
	GLuint VBO;
	int type_model;
};

