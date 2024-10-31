#include "DrawableObject.h"

DrawableObject::DrawableObject(Camera* _camera) : shaderProgram(nullptr), model(nullptr), rotateAngle(0), rotateX(0), rotateY(0), rotateZ(0)
{
	model = new Model();
	transformation = new Transformation();
}

DrawableObject::~DrawableObject() {}


void DrawableObject::init_model(Model* model)
{
	this->model = model;
}




void DrawableObject::init_shader(ShaderProgram* shaderprogram)
{
	shaderProgram = shaderprogram;
}


void DrawableObject::Draw()
{
	glm::mat4 modelMatrix = transformation->getModelMatrix();
	
	shaderProgram->setUniformLocation("modelMatrix", modelMatrix);
	shaderProgram->setUniformLocation("objectColor", color);
	shaderProgram->use_shader();
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


void DrawableObject::setColor(glm::vec4 _color)
{
	color = _color;
}