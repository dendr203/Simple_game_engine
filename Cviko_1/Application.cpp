#include "Application.h"

#include <stdio.h>
#include <stdlib.h>

int naklon = 0;


Application::Application() {}

Application::~Application() {}

void Application::initialization()
{
	window = new Window(1000, 800);
	scene = new Scene();
}

//toto tu nebude, bude to v scénì ty inity jednotlivé na objekty
void Application::createModels()
{
	//scene->CrateScene();
	//scene->CreateForestScene(10, 10);
	scene->CreateCameraBaseScene();
}

void Application::run()
{	
	glEnable(GL_DEPTH_TEST);//Do depth comparisons and update the depth buffer.
	while (!window->shouldClose()) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		HandleInput();
		scene->DrawScene();
		
		window->poolEvents();
		window->swapBuffers();
	}

	exit(EXIT_SUCCESS);
}


void Application::HandleInput() 
{

	int key = window->pressedKey;
	if (key == 1) {
		scene->SwitchScene(1); // Pøepnout na normální scénu
		window->pressedKey = 0;
	}
	else if (key == 2) {
		scene->SwitchScene(2); // Pøepnout na scénu lesa
		window->pressedKey = 0;
	}
}


