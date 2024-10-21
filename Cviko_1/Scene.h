#pragma once
#include "DrawableObject.h"
#include "Camera.h"

#include <vector>

class Scene
{
public:
	Scene();
	~Scene();

	void init_cameraScene(Camera* _camera);
	void CrateScene();
	void CreateForestScene(int numTrees, int numBushes);
	void CreateConstantTestScene();

	void DrawScene();
	void ClearScene();
	void SwitchScene(int sceneId);


private:
	std::vector<DrawableObject*> objects;
	void RandomTransform(DrawableObject* object, int i);
	Camera* camera;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
};

