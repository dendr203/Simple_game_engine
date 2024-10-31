#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "Observer.h"
#include "Camera.h"
#include "Light.h"

#include "ShaderLoader.h"

class Light;
class Camera;
class ShaderProgram : public Observer, public ShaderLoader
{
public:
	ShaderProgram(Camera* camera, Light* light);
	~ShaderProgram();

	void init_shader(const char* vertex_shader_str, const char* fragment_shader_str);
	void use_shader();


	void setUniformLocation(const char* name, const glm::mat4& matrix);
	void setUniformLocation(const char* name, const glm::vec3& vector);
	void setUniformLocation(const char* name, const glm::vec4& vector);
	void setUniformLocation(const char* name, float _float);

	void updateFromSubject();
	void setProjectionMatrix();

private:
	Camera* camera;
	Light* light;

	GLuint getLocation(const char* name);
};

