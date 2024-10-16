#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <vector>

class Model
{
public:
	Model();
	~Model();
	void init_model(std::vector<float>& model);
	void draw_model();

private:
	 GLuint VBO;
	 GLuint VAO;
	 
	 std::vector<float> model;
};


