#include "Window.h"

#include <stdlib.h>
#include <stdio.h>

Window::Window()
{
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}
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