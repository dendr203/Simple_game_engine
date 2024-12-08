#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"
#include "Model.h"
#include "Material.h"
#include "TexturedModel.h"
#include "MeshModel.h"

#include "TransformationComposite.h"
#include "Translation.h"
#include "Rotation.h"
#include "Scaling.h"
#include "DynamicRotation.h"
#include "BezierCurve.h"


#include <vector>


#include "Models/sphere.h"
#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/gift.h"
#include "Models/plain.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/plain_texture.h"
#include "Models/house.h"


class DrawableObject
{
public:
	DrawableObject(BezierCurve* curve = nullptr, bool is_plain = false);
	~DrawableObject();

	void init_model(Model* model, int is_skybox = 0);
	int is_Skybox() { return is_skybox; }

	void init_shader(ShaderProgram* shaderprogram);
	void Draw(float deltaTime);
	void DrawSkybox(bool followCamera);


	void addScale(glm::vec3 scaleVector);
	void addTranslation(glm::vec3 translateVector);
	void addRotation(float angle, glm::vec3 axis);
	void addDynamicRotation(float speed, glm::vec3 axis);
	void clearTransformations();


	glm::mat4 getModelMatrix(float deltaTime);


	void setColor(glm::vec4 _color);
	void setMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);

	int getID() { return objectID; }

private:
	int is_skybox;
	ShaderProgram* shaderProgram;
	Model* model;
	Material* material;

	TransformationComposite* transformationComposite;

	glm::vec4 color;

	int objectID;
	static int nextID;

	BezierCurve* curve;
};

