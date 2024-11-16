#pragma once
#include "DrawableObject.h"
#include "Camera.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"

#include <vector>

class Scene
{
public:
	Scene(Camera* _camera);
	~Scene();

	void CreateForestScene_blud(int numTrees, int numBushes);
	void CreateForestScene_bat(int numTrees, int numBushes);
	void CreateFourShaderLightsScene();
	void CreateMultipleLightsScene();

	void DrawScene(float deltaTime);
	void ClearScene();
	void SwitchScene(int sceneId);


private:
	std::vector<DrawableObject*> objects;
	void RandomTransform(DrawableObject* object, float scale_base);
	Camera* camera;

	
	std::vector<Light*> lights;
	std::vector<ShaderProgram*> shaderPrograms;
	std::vector<Model*> models;


};

