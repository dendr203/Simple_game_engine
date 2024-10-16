#include "DrawableObject.h"






DrawableObject::DrawableObject()
{
	model = new Model();
	shaderProgram = new ShaderProgram();
	transformation = new Transformation();
}

DrawableObject::~DrawableObject()
{
	delete model;
	delete shaderProgram;
	delete transformation;

}

void DrawableObject::init_sphere()
{
	vector_model = std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0]));
	model->init_model(vector_model);
}

void DrawableObject::init_tree()
{
	vector_model = std::vector<float>(tree, tree + sizeof(tree) / sizeof(tree[0]));
	model->init_model(vector_model);
}

void DrawableObject::init_bushes()
{
	vector_model = std::vector<float>(bushes, bushes + sizeof(bushes) / sizeof(bushes[0]));
	model->init_model(vector_model);
}

void DrawableObject::init_sphere_camera()
{
	vector_model = std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0]));
	model->init_model(vector_model);
}




void DrawableObject::init_shader(const char* vertex_shader_str, const char* fragment_shader_str)
{
	shaderProgram->init_shader(vertex_shader_str, fragment_shader_str);
}


void DrawableObject::Draw(glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
{
	glm::mat4 modelMatrix = transformation->getModelMatrix();
	
	shaderProgram->use_shader();

	GLint modelLoc = glGetUniformLocation(shaderProgram->GetShader(), "modelMatrix");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	
	GLint viewLoc = glGetUniformLocation(shaderProgram->GetShader(), "viewMatrix");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	GLint projLoc = glGetUniformLocation(shaderProgram->GetShader(), "projectMatrix");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	


	model->draw_model();
}


void DrawableObject::scale(float x, float y, float z)
{
	transformation->scale(x, y, z);
}

void DrawableObject::translate(float x, float y, float z)
{
	transformation->translate(x, y, z);
}

void DrawableObject::rotate(float angle, float x, float y, float z)
{
	transformation->rotate(angle, x, y, z);
}