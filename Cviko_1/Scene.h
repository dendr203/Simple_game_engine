#pragma once

#include <vector>

#include "DrawableObject.h"

class Scene
{
public:
	Scene();
	~Scene();
	void CrateScene();
	void CreateForestScene(int numTrees, int numBushes);
	void RandomTransform(DrawableObject* object);

	void AddObject(DrawableObject* object);
	void DrawScene(int angle);
	void ClearScene();
	void SwitchScene(int sceneId);
private:
	std::vector<DrawableObject*> objects;
};

