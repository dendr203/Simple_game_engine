#include "Application.h"

#include <stdio.h>
#include <stdlib.h>

int naklon = 0;


Application::Application()
	: camera(new Camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f))) {}

Application::~Application() {
	delete camera;
	delete window;
	delete scene;
}

void Application::initialization()
{
	window = new Window(1000, 800);

	scene = new Scene(camera);
}


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

	if (Window::keyStates[GLFW_KEY_W]) {
		camera->move(camera->front, 0.1f); // Adjust speed as needed
	}
	if (Window::keyStates[GLFW_KEY_S]) {
		camera->move(-camera->front, 0.1f);
	}
	if (Window::keyStates[GLFW_KEY_A]) {
		camera->move(-glm::normalize(glm::cross(camera->front, camera->up)), 0.1f);
	}
	if (Window::keyStates[GLFW_KEY_D]) {
		camera->move(glm::normalize(glm::cross(camera->front, camera->up)), 0.1f);
	}

	if (Window::keyStates[GLFW_KEY_1]) {
		scene->SwitchScene(1); // Pøepnout na normální scénu
	}
	if (Window::keyStates[GLFW_KEY_2]) {
		scene->SwitchScene(2); // Pøepnout na scénu lesa
	}
}


