#include "Triangle.h"

Triangle::Triangle() : points{
	 0.0f, 0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
}
{

}

void Triangle::Init(const char* vertex_shader, const char* fragment_shader)
{
	VBO = VertexBufferObject();
	VAO = VertexArrayObject();
	VBO.Init(points, size);
	VAO.Init(3, VBO);
	shader = Shader();
	shader.Init(vertex_shader, fragment_shader);
}
