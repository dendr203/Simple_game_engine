#include "VertexArrayObject.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "VertexBufferObject.h"

VertexArrayObject::VertexArrayObject(){}

void VertexArrayObject::Init(int num_of_edges, VertexBufferObject& VBO)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO.GetVBO());

	if (num_of_edges == 3)
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}
	else if (num_of_edges == 4)
	{
		glEnableVertexAttribArray(1); //barvy pøímo ze struktury z fragment shaderu
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0); //pozice
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(float) * 4)); // barva
	}
}

VertexArrayObject::~VertexArrayObject()
{

}


GLuint VertexArrayObject::GetVAO()
{
	return VAO;
}