#include "DrawableObject.h"

DrawableObject::DrawableObject(Camera* _camera) : rotateAngle(0), rotateX(0), rotateY(0), rotateZ(0)
{
	model = new Model();
	shaderProgram = new ShaderProgram(_camera);
	_camera->addObserver(shaderProgram);
	transformation = new Transformation();
}

DrawableObject::~DrawableObject()
{
	delete shaderProgram;
	delete transformation;

}

/*
void DrawableObject::init_sphere(std::vector<float>& vector_model)
{
	//vector_model = std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0]));
	model->init_model(vector_model);
}

void DrawableObject::init_tree(std::vector<float>& vector_model)
{
	//vector_model = std::vector<float>(tree, tree + sizeof(tree) / sizeof(tree[0]));
	model->init_model(vector_model);
}

void DrawableObject::init_bushes(std::vector<float>& vector_model)
{
	//vector_model = std::vector<float>(bushes, bushes + sizeof(bushes) / sizeof(bushes[0]));
	model->init_model(vector_model);
}

void DrawableObject::init_plainstd::vector<float>& vector_model()
{
	//vector_model = std::vector<float>(plain, plain + sizeof(plain) / sizeof(plain[0]));
	model->init_model(vector_model);
}
*/


void DrawableObject::init_model(Model* model)
{
	this->model = model;
}




void DrawableObject::init_shader(const char* vertex_shader_str, const char* fragment_shader_str)
{
	shaderProgram->init_shader(vertex_shader_str, fragment_shader_str);
}


void DrawableObject::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	glm::mat4 modelMatrix = transformation->getModelMatrix();
	
	shaderProgram->use_shader();
	shaderProgram->setMatrixUniform("modelMatrix", modelMatrix);
	
	shaderProgram->setMatrixUniform("viewMatrix", viewMatrix);
	shaderProgram->setMatrixUniform("projectionMatrix", projectionMatrix);



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