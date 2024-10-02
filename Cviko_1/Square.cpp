#include "Square.h"

Square::Square() : points{
	 0.9f, 0.9f, 0.0f,
	 0.9f, 0.7f, 0.0f,
	 0.7f, 0.7f, 0.0f,

	 0.7f, 0.7f, 0.0f,
	 0.7f, 0.9f, 0.0f,
	 0.9f, 0.9f, 0.0f,
}
{

}

void Square::Init(const char* vertex_shader, const char* fragment_shader)
{
	VBO = VertexBufferObject();
	VAO = VertexArrayObject();
	VBO.Init(points, size);
	VAO.Init(3, VBO);
	shader = Shader();
	shader.Init(vertex_shader, fragment_shader);
}

