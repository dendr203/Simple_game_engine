#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"
#include "Model.h"
#include "Transformation.h"

#include <vector>

#include "Models/sphere.h"
#include "Models/tree.h"


class DrawableObject
{
public:
	DrawableObject();
	~DrawableObject();
	void init_sphere();
	void init_tree();
	void Draw();

	void setTransformation(const Transformation& transformation);
	
private:
	ShaderProgram* shaderProgram;
	Model* model;

	std::vector<float> vector_model;
	Transformation transformation;
};

