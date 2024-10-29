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
class ShaderProgram : public Observer
{
public:
	ShaderProgram(Camera* camera, Light* light);
	~ShaderProgram();

	void init_shader(const char* vertex_shader_str, const char* fragment_shader_str);
	void use_shader();


	void setMatrixUniform(const char* name, const glm::mat4& matrix);
	void setVector3Uniform(const char* name, const glm::vec3& vector);
	void setVector4Uniform(const char* name, const glm::vec4& vector);
	void setFloatUniform(const char* name, float _float);

	void updateFromSubject();

private:
	GLuint shaderProgram_id;

	ShaderLoader* shaderLoader;

	Camera* camera;
	Light* light;
};

