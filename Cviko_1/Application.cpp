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
	window->attachScene(scene);
}


void Application::createModels()
{
	//scene->CreateForestScene(50, 50);
	//scene->CreateCameraBaseScene();
	//scene->CreateConstantTestScene();
	//scene->CreateFourShaderLightsScene();
	//scene->CreateMultipleLightsScene();
	scene->CreateTexturedScene();
}


void Application::run()
{	
	auto previousTime = std::chrono::high_resolution_clock::now(); //dynamic rotation will be dependent on framerate

	glEnable(GL_DEPTH_TEST);//Do depth comparisons and update the depth buffer.
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	while (!window->shouldClose()) {
		auto currentTime = std::chrono::high_resolution_clock::now();
		float deltaTime = std::chrono::duration<float>(currentTime - previousTime).count();
		previousTime = currentTime;

		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		scene->DrawSkybox(deltaTime);
		scene->DrawScene(deltaTime);
		
		window->poolEvents();
		HandleInput();

		window->swapBuffers();
	}

	glDisable(GL_STENCIL_TEST);

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
	if (Window::keyStates[GLFW_KEY_5]) {
		scene->SwitchScene(5);
		Window::keyStates[GLFW_KEY_5] = false;
	}
	if (Window::keyStates[GLFW_KEY_Q]) {
		scene->skyboxFollowCamera = !scene->skyboxFollowCamera;
		Window::keyStates[GLFW_KEY_Q] = false;
	}


	// Process mouse movement only if there are offsets
    if ((Window::out_x != 0 || Window::out_y != 0) && Window::keyStates[GLFW_MOUSE_BUTTON_RIGHT]) {
        camera->processMouseMovement(Window::out_x, Window::out_y);
        
        Window::out_x = 0;
        Window::out_y = 0;
    }

	
}


