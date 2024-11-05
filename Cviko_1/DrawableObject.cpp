#include "DrawableObject.h"

DrawableObject::DrawableObject(Camera* _camera) : shaderProgram(nullptr), model(nullptr), color(0)
{
	transformationComposite = new TransformationComposite();
}

DrawableObject::~DrawableObject() {}


void DrawableObject::init_model(Model* model)
{
	this->model = model;
}




void DrawableObject::init_shader(ShaderProgram* shaderprogram)
{
	shaderProgram = shaderprogram;
	shaderProgram->setLightPosition();
	shaderProgram->setLightColor();
	shaderProgram->setAmbient();
	shaderProgram->setShinines();
}


void DrawableObject::Draw()
{
	//zde posílat pozdìji celou transformaci nejlépe
	shaderProgram->setModelMatrix(getModelMatrix());
	shaderProgram->setObjectColor(color);
	
	shaderProgram->use_shader();
	model->draw_model();
}


void DrawableObject::addScale(float x, float y, float z)
{
	transformationComposite->AddTransformation(new Scaling(x, y, z));
}

void DrawableObject::addTranslation(float x, float y, float z)
{
	transformationComposite->AddTransformation(new Translation(x, y, z));
}

void DrawableObject::addRotation(float angle, float x, float y, float z)
{
	transformationComposite->AddTransformation(new Rotation(angle, glm::vec3(x, y, z)));
}

void DrawableObject::clearTransformations()
{
	transformationComposite->clearTransformations();
}


glm::mat4 DrawableObject::getModelMatrix() 
{
	glm::mat4 modelMatrix = glm::mat4(1.0f); // Základní jednotková matice
	transformationComposite->transform(modelMatrix); // Aplikuj transformace na jednotkovou matici
	return modelMatrix;
}


void DrawableObject::setColor(glm::vec4 _color)
{
	color = _color;
}