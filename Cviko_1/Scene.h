#pragma once

#include <vector>

#include "DrawableObject.h"
#include "Transformation.h"

class Scene
{
public:
	Scene();
	~Scene();
	void CrateScene();
	void AddObject(DrawableObject* object);
	
	void DrawScene(int angle);
private:
	std::vector<DrawableObject*> objects;
	
	//odstranit potom co bude hotove
	Transformation transformation;
};

