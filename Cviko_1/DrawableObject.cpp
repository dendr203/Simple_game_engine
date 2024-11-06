#include "DrawableObject.h"

DrawableObject::DrawableObject(Camera* _camera) : shaderProgram(nullptr), model(nullptr), color(0), dynamicRotation(nullptr)
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
	shaderProgram->setLights();
}

void DrawableObject::updateTime(float deltaTime)
{
	if (dynamicRotation)
	{
		dynamicRotation->update(deltaTime);
	}
}

void DrawableObject::Draw()
{
	//zde posílat pozdìji celou transformaci nejlépe
	shaderProgram->setModelMatrix(getModelMatrix());
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
	dynamicRotation = new DynamicRotation(speed, axis);
	transformationComposite->AddTransformation(dynamicRotation);
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