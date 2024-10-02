#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>  

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <memory> //smart pointers

#include "Window.h"
#include "Triangle.h"
#include "Square.h"
#include "Shader.h"


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
	Window* window = new Window();
	

	Triangle* triangle = new Triangle();
	Square* square = new Square();
};




