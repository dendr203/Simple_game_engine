#include "DrawableObject.h"

DrawableObject::DrawableObject(Camera* _camera) : shaderProgram(nullptr), model(nullptr), color(0)
{
	transformationComposite = new TransformationComposite();
}

DrawableObject::~DrawableObject()
{
	delete transformationComposite;
}


void DrawableObject::init_model(Model* model)
{
	this->model = model;
}




void DrawableObject::init_shader(ShaderProgram* shaderprogram)
{
	shaderProgram = shaderprogram;
	shaderProgram->setLights();
}


void DrawableObject::Draw(float deltaTime)
{
	//zde posílat pozdìji celou transformaci nejlépe
	shaderProgram->setModelMatrix(getModelMatrix(deltaTime));
	shaderProgram->setObjectColor(color);
	
	shaderProgram->use_shader();
	
	model->draw_model();
}


void DrawableObject::addScale(glm::vec3 scaleVector)
{
	transformationComposite->AddTransformation(new Scaling(scaleVector));
}

void DrawableObject::addTranslation(glm::vec3 translateVector)
{
	transformationComposite->AddTransformation(new Translation(translateVector));
}

void DrawableObject::addRotation(float angle, glm::vec3 axis)
{
	transformationComposite->AddTransformation(new Rotation(angle, axis));
}

void DrawableObject::addDynamicRotation(float speed, glm::vec3 axis)
{
	transformationComposite->AddTransformation(new DynamicRotation(speed, axis));
}

void DrawableObject::clearTransformations()
{
	transformationComposite->clearTransformations();
}

glm::mat4 DrawableObject::getModelMatrix(float deltaTime) 
{
	glm::mat4 modelMatrix = glm::mat4(1.0f); // Základní jednotková matice
	transformationComposite->transform(modelMatrix, deltaTime); // Aplikuj transformace na jednotkovou matici
	return modelMatrix;
}


void DrawableObject::setColor(glm::vec4 _color)
{
	color = _color;
}