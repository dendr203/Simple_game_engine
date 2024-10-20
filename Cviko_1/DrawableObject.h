#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"
#include "Model.h"
#include "Transformation.h"

#include <vector>

#include "Models/sphere.h"
#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/gift.h"
#include "Models/plain.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"


class DrawableObject
{
public:
	DrawableObject(Camera* _camera);
	~DrawableObject();


	void init_sphere();
	void init_tree();
	void init_bushes();
	void init_plain();

	void init_model(Model* model);


	void init_shader(const char* vertex_shader_str, const char* fragment_shader_str);
	void Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

	
	//this will be done differently in future
	void scale(float x, float y, float z);
	void translate(float x, float y, float z);
	void rotate(float angle, float x, float y, float z);
	float rotateAngle;
	float rotateX;
	float rotateY;
	float rotateZ;

private:
	ShaderProgram* shaderProgram;
	Model* model;

	//std::vector<float> vector_model;
	Transformation* transformation;

	
};

