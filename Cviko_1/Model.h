#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <vector>

class Model
{
public:
	Model(const std::vector<float>& vertices);
	~Model();
	void draw_model();

private:
	 GLuint VBO, VAO;
	 GLsizei numVertices;

	 void init_model(const std::vector<float>& verticies);
};


