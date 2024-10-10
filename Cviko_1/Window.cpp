#include "Window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

Window::Window(int witdth, int height)
{
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

	window = glfwCreateWindow(witdth, height, "ZPG", NULL, NULL);
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


int Window::pressedKey = 0;
void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		pressedKey = 1;
	}
	else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		pressedKey = 2;
	}

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Window::window_focus_callback(GLFWwindow* window, int focused)
{ 
	printf("window_focus_callback \n");
}

void Window::window_iconify_callback(GLFWwindow* window, int iconified) 
{ 
	printf("window_iconify_callback \n");
}

void Window::window_size_callback(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Window::cursor_callback(GLFWwindow* window, double x, double y) 
{ 
	printf("cursor_callback \n"); 
}

void Window::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);

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
