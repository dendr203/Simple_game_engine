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
	void CreateTexturedScene();


	void CreateSkybox();
	void DrawSkybox(float deltaTime);

	void DrawScene(float deltaTime);
	void ClearScene();
	void SwitchScene(int sceneId);
	

	bool skyboxFollowCamera = true;

private:
	std::vector<DrawableObject*> objects;
	void RandomTransform(DrawableObject* object, float scale_base);
	Camera* camera;

	
	std::vector<Light*> lights;
	std::vector<ShaderProgram*> shaderPrograms;
	std::vector<Model*> models;

	std::vector<Texture*> textures;
};

