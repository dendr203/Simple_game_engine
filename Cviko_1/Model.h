#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <vector>

class Model
{
public:
	Model(const std::vector<float>& vertices);
	~Model();
	virtual void draw_model();

protected:
	GLuint VBO, VAO, IBO;
	GLsizei numVertices;

	virtual void init_model(const std::vector<float>& verticies);
};


