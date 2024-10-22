#include "Application.h"

#include <stdio.h>
#include <stdlib.h>

int naklon = 0;


Application::Application() {}

Application::~Application() {
	delete camera;
	delete window;
	delete scene;
}

void Application::initialization()
{
	window = new Window(1000, 800);
	camera = new Camera(glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.05, 45.0, window->getAspect_ratio(), -90.f, 0.f, 0.08f);
	//camera = new Camera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0.f, 45.0, window->getAspect_ratio(), -90.0f, -90.0f, 0.f);
	
	scene = new Scene();
	scene->init_cameraScene(camera);
}


void Application::createModels()
{
	//scene->CrateScene();
	scene->CreateForestScene(50, 50);
	//scene->CreateCameraBaseScene();
	//scene->CreateConstantTestScene();
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
	if (Window::keyStates[GLFW_KEY_W]) {
		camera->moveForward();
	}
	if (Window::keyStates[GLFW_KEY_S]) {
		camera->moveBackwards();
	}
	if (Window::keyStates[GLFW_KEY_A]) {
		camera->moveLeft();
	}
	if (Window::keyStates[GLFW_KEY_D]) {
		camera->moveRight();
	}

	if (Window::keyStates[GLFW_KEY_1]) {
		scene->SwitchScene(1);
		Window::keyStates[GLFW_KEY_1] = false;
	}
	if (Window::keyStates[GLFW_KEY_2]) {
		scene->SwitchScene(2);
		Window::keyStates[GLFW_KEY_2] = false;
	}


	// Process mouse movement only if there are offsets
    if (Window::out_x != 0 || Window::out_y != 0) {
        camera->processMouseMovement(Window::out_x, Window::out_y);
        
        Window::out_x = 0;
        Window::out_y = 0;
    }
}


