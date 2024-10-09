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
	scene->CrateScene();
}

//toto tu nebude, bude to v scénì ty inity jednotlivé na objekty
void Application::createModels()
{
	//drawableObject->init_sphere();
	//drawableObject->init_tree();
}

void Application::run()
{
	float angle = 0.0f;
	

	glEnable(GL_DEPTH_TEST);//Do depth comparisons and update the depth buffer.
	while (!window->shouldClose()) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		


		if (angle > 1.0f)
		{
			angle = 0;
		}
		else
		{
			angle += 0.1f;
		}

		//trans.rotate(angle, 0.0f, 1.0f, 0.0f);

		scene->DrawScene(angle);
		
		window->poolEvents();
		window->swapBuffers();
	}

	exit(EXIT_SUCCESS);
}


