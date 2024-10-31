#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"
#include "Model.h"
#include "TransformationComposite.h"

//maybe different next time
#include "Translation.h"
#include "Rotation.h"
#include "Scaling.h"


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

	void init_model(Model* model);


	void init_shader(ShaderProgram* shaderprogram);
	void Draw();

	
	//this will be done differently in future
	void addScale(float x, float y, float z);
	void addTranslation(float x, float y, float z);
	void addRotation(float angle, float x, float y, float z);
	void clearTransformations();


	glm::mat4 getModelMatrix();


	void setColor(glm::vec4 _color);

private:
	ShaderProgram* shaderProgram;
	Model* model;

	TransformationComposite* transformationComposite;

	glm::vec4 color;
};

