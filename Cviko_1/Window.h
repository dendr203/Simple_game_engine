#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include <unordered_map>

#include "Camera.h"

class Window
{
public:
	Window(int width, int height);
	~Window();

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, float x, float y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);

	float getAspect_ratio();
	
	static std::unordered_map<int, bool> keyStates;
	static float out_x, out_y;

	float lastX;
	float lastY;

	int width, height;
	float ratio;

	bool shouldClose();
	void poolEvents();
	void swapBuffers();

	void attachCamera(Camera* _camera);

private:
	GLFWwindow* window;
	int major, minor, revision;
	
	Camera* camera;
};

