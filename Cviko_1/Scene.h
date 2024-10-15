#pragma once
#include "DrawableObject.h"

#include <vector>

class Scene
{
public:
	Scene();
	~Scene();
	void CrateScene();
	void CreateForestScene(int numTrees, int numBushes);
	void CreateCameraBaseScene();

	void AddObject(DrawableObject* object);
	void DrawScene();
	void ClearScene();
	void SwitchScene(int sceneId);
private:
	std::vector<DrawableObject*> objects;
	void RandomTransform(DrawableObject* object);
};

