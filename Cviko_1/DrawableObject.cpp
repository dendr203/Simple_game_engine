#include "DrawableObject.h"

int DrawableObject::nextID = 1;


DrawableObject::DrawableObject(BezierCurve* curve, bool is_plain) 
	: curve(curve), shaderProgram(nullptr), model(nullptr), color(0), objectID(nextID++)
{
	transformationComposite = new TransformationComposite();
	if (is_plain == true)
	{
		objectID = 0;
	}
}

DrawableObject::~DrawableObject()
{
	delete material;
	delete transformationComposite;
	if (objectID != 0)
	{
		nextID--;
	}
}


void DrawableObject::init_model(Model* model, int is_skybox)
{
	this->is_skybox = is_skybox;
	this->model = model;
}




void DrawableObject::init_shader(ShaderProgram* shaderprogram)
{
	shaderProgram = shaderprogram;
}


void DrawableObject::Draw(float deltaTime)
{
	shaderProgram->setLights();

	shaderProgram->setModelMatrix(getModelMatrix(deltaTime));
	shaderProgram->setObjectColor(color);
	if (material != nullptr)
	{
		shaderProgram->setMaterial(*material);
	}

	if (TexturedModel* texturedModel = dynamic_cast<TexturedModel*>(model))
	{ 
		shaderProgram->setTexture(texturedModel->getUnitID(), texturedModel->getScale());
	}

	if (MeshModel* meshModel = dynamic_cast<MeshModel*>(model))
	{
		shaderProgram->setTexture(meshModel->getUnitID(), meshModel->getScale());
	}
	
	shaderProgram->use_shader();
	model->draw_model();
	shaderProgram->unuse_Shader();

	if (TexturedModel* texturedModel = dynamic_cast<TexturedModel*>(model))
	{
		shaderProgram->unsetTexture();
	}
}

void DrawableObject::DrawSkybox(bool followCamera)
{
	shaderProgram->setSkyboxTexture(followCamera);

	shaderProgram->use_shader();
	model->draw_model();
	shaderProgram->unuse_Shader();

	shaderProgram->unsetTexture();
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
	
	if (curve != nullptr)
	{
		modelMatrix = curve->getModelMatrix(deltaTime);
	}
	
	transformationComposite->transform(modelMatrix, deltaTime); // Aplikuj transformace na matici
	return modelMatrix;
}


void DrawableObject::setColor(glm::vec4 _color)
{
	color = _color;
}

void DrawableObject::setMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
{
	material = new Material(ambient, diffuse, specular, shininess);
}