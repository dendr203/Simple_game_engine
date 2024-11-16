#include "Window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>





Window::Window(int width, int height) : ratio(0), width(0), height(0), lastX(0), lastY(0), camera(nullptr)
{
	lastX = (float) width / 2;
	lastY = (float) height / 2;
	


	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	/* //inicializace konkretni verze
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
	GLFW_OPENGL_CORE_PROFILE);  //*/

	window = glfwCreateWindow(width, height, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetWindowUserPointer(window, this);  // Set the user pointer to this instance

	glfwSetCursorPosCallback(window, [](GLFWwindow* win, double x, double y) {
		Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(win));
		if (instance) {
			instance->cursor_callback(win, x, y);
		}
		});

	glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
		Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(win));
		if (instance) {
			instance->key_callback(win, key, scancode, action, mods);
		}
		});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* win, int button, int action, int mods) {
		Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(win));
		if (instance) {
			instance->button_callback(win, button, action, mods);
		}
		});

	glfwSetWindowSizeCallback(window, [](GLFWwindow* win, int width, int height) {
		Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(win));
		if (instance) {
			instance->window_size_callback(win, width, height);
		}
		});


	glfwSetWindowIconifyCallback(window, [](GLFWwindow* win, int iconified) {
		Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(win));
		if (instance) {
			instance->window_iconify_callback(win, iconified);
		}
		});



	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);



	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}




void Window::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}


std::unordered_map<int, bool> Window::keyStates;

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		keyStates[key] = true; // Klávesa je stisknuta
	}
	else if (action == GLFW_RELEASE) {
		keyStates[key] = false; // Klávesa je uvolnìna
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	//printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Window::window_focus_callback(GLFWwindow* window, int focused)
{ 
	printf("window_focus_callback \n");
}

void Window::window_iconify_callback(GLFWwindow* window, int iconified) 
{ 
	printf("window_iconify_callback \n");
}

void Window::window_size_callback(GLFWwindow* window, int _width, int _height)
{
	Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
	
	if (instance)
	{
		if (_height == 0) {
			_height = 1;  // Aby se pøedešlo dìlení nulou
		}

		instance->width = _width;
		instance->height = _height;

		instance->ratio = (float) instance->width / (float)instance->height;

		//printf("resize %d, %d \n", _width, _height);
		glViewport(0, 0, instance->width, instance->height);

		if (instance->camera)
		{
			instance->camera->updateAspectRatio(instance->ratio);
		}
		else
		{
			printf("Camera is not attached to window!!!\n");
		}
	}
	

}



static bool firstMouse = true;
float Window::out_x, Window::out_y;

void Window::cursor_callback(GLFWwindow* window, float x, float y) 
{ 
	Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (instance)
	{
		if (firstMouse)
		{
			instance->lastX = x;
			instance->lastY = y;
			firstMouse = false;
		}

		out_x = x - instance->lastX;
		out_y = instance->lastY - y;

		instance->lastX = x;
		instance->lastY = y;
	}

	//printf("cursor_callback \n"); 
}




void Window::button_callback(GLFWwindow* window, int button, int action, int mode)
{

	if (action == GLFW_PRESS) {
		keyStates[button] = true;
	}
	else if (action == GLFW_RELEASE) {
		keyStates[button] = false;
	}

	//printf("button_callback [%d,%d,%d]\n", button, action, mode);

}

float Window::getAspect_ratio()
{
	return ratio;
}


bool Window::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::poolEvents()
{
	// update other events like input handling
	glfwPollEvents();
}

void Window::swapBuffers()
{
	// put the stuff we’ve been drawing onto the display
	glfwSwapBuffers(window);
}

void Window::attachCamera(Camera* _camera)
{
	camera = _camera;
}
