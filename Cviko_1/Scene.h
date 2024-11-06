#pragma once
#include "DrawableObject.h"
#include "Camera.h"

#include <vector>

class Scene
{
public:
	Scene(Camera* _camera);
	~Scene();

	void CreateForestScene(int numTrees, int numBushes);
	void CreateLightTestScene();
	void CreateFourShaderLightsScene();
	void CreateMultipleLightsScene();

	void DrawScene();
	void ClearScene();
	void SwitchScene(int sceneId);


private:
	std::vector<DrawableObject*> objects;
	void RandomTransform(DrawableObject* object, int i, float scale_base);
	Camera* camera;

	
	std::vector<Light*> lights;
	std::vector<ShaderProgram*> shaderPrograms;
	std::vector<Model*> models;
};

