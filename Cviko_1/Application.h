#pragma once

#include "Window.h"
#include "Scene.h"
#include "Camera.h"


class Application
{
public:
	Application();
	~Application();
	void initialization();
	void createShaders();
	void createModels();
	void run();

	void HandleInput();

private:
	Window* window;
	Scene* scene;	
	Camera* camera;
};




