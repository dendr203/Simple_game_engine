#pragma once
#include "DrawableObject.h"
#include "Camera.h"

#include <vector>

class Scene
{
public:
	Scene(Camera* _camera);
	~Scene();
	void CrateScene();
	void CreateForestScene(int numTrees, int numBushes);
	void CreateCameraBaseScene();

	void DrawScene();
	void ClearScene();
	void SwitchScene(int sceneId);


private:
	std::vector<DrawableObject*> objects;
	void RandomTransform(DrawableObject* object, int i);
	Camera* camera;
};

