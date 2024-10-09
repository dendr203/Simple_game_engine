#pragma once

#include "Window.h"
#include "Scene.h" 


class Application
{
public:
	Application();
	~Application();
	void initialization();
	void createShaders();
	void createModels();
	void run();

private:
	Window* window;

	Scene* scene;	
};




