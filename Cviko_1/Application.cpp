#include "Application.h"

#include <stdio.h>
#include <stdlib.h>

int naklon = 0;


Application::Application() : camera(nullptr), scene(nullptr), window(nullptr) {}

Application::~Application() {
	delete camera;
	delete window;
	delete scene;
}

void Application::initialization()
{
	window = new Window(1000, 800);
	camera = new Camera(window->getAspect_ratio());
	window->attachCamera(camera);
	
	scene = new Scene(camera);
}


void Application::createModels()
{
	//scene->CrateScene();
	//scene->CreateForestScene(50, 50);
	//scene->CreateCameraBaseScene();
	//scene->CreateConstantTestScene();
	scene->CreateFourShaderLightsScene();
}

void Application::run()
{	
	glEnable(GL_DEPTH_TEST);//Do depth comparisons and update the depth buffer.
	while (!window->shouldClose()) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		window->poolEvents();

		HandleInput();
		scene->DrawScene();
		
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
	if (Window::keyStates[GLFW_KEY_3]) {
		scene->SwitchScene(3);
		Window::keyStates[GLFW_KEY_3] = false;
	}
	if (Window::keyStates[GLFW_KEY_4]) {
		scene->SwitchScene(4);
		Window::keyStates[GLFW_KEY_4] = false;
	}


	// Process mouse movement only if there are offsets
    if ((Window::out_x != 0 || Window::out_y != 0) && Window::keyStates[GLFW_MOUSE_BUTTON_RIGHT]) {
        camera->processMouseMovement(Window::out_x, Window::out_y);
        
        Window::out_x = 0;
        Window::out_y = 0;
    }
}


