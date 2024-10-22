#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "Observer.h"
#include "Shader.h"
#include "Camera.h"
#include "Light.h"

class Light;
class Camera;
class ShaderProgram : public Observer
{
public:
	ShaderProgram(Camera* camera, Light* light);
	~ShaderProgram();

	void init_shader(const char* vertex_shader_str, const char* fragment_shader_str);
	void use_shader();
	GLuint GetShader();

	void setMatrixUniform(const char* name, const glm::mat4& matrix);
	void setVector3Uniform(const char* name, const glm::vec3& vector);
	void setVector4Uniform(const char* name, const glm::vec4& vector);

	void updateFromCam();

private:
	GLuint shaderProgram_id;

	Camera* camera;
	Light* light;
};

