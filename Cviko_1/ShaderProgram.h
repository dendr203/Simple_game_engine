#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "Shader.h"
#include "Camera.h"

class Camera;
class ShaderProgram
{
public:
	ShaderProgram(Camera* camera);
	~ShaderProgram();

	void init_shader(const char* vertex_shader_str, const char* fragment_shader_str);
	void use_shader();
	GLuint GetShader();

	void setMatrixUniform(const char* name, const glm::mat4& matrix);

	void updateFromCam();

private:
	GLuint shaderProgram_id;

	Camera* camera;
};

