#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Camera* _camera) : shaderProgram_id(-1), camera(_camera) {}

ShaderProgram::~ShaderProgram() {}

void ShaderProgram::init_shader(const char* vertex_shader_str, const char* fragment_shader_str)
{
	Shader* vertex_shader = new Shader();
	vertex_shader->init_shader(GL_VERTEX_SHADER, vertex_shader_str);

	Shader* fragment_shader = new Shader();
	fragment_shader->init_shader(GL_FRAGMENT_SHADER, fragment_shader_str);

	shaderProgram_id = glCreateProgram();
	glAttachShader(shaderProgram_id, fragment_shader->GetShader());
	glAttachShader(shaderProgram_id, vertex_shader->GetShader());
	glLinkProgram(shaderProgram_id);

	GLint status;
	glGetProgramiv(shaderProgram_id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgram_id, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgram_id, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		exit(EXIT_FAILURE);
	}

	// Smažeme shadery, už je nepotøebujeme po linkování
	glDeleteShader(vertex_shader->GetShader());
	glDeleteShader(fragment_shader->GetShader());



}

void ShaderProgram::use_shader()
{
	glUseProgram(shaderProgram_id);
}

GLuint ShaderProgram::GetShader()
{
	return shaderProgram_id;
}


void ShaderProgram::setMatrixUniform(const char* name, const glm::mat4& matrix) {
	GLuint location = glGetUniformLocation(shaderProgram_id, name);
	if (location != -1) {
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	else {
		printf("Uniform %s not found!\n", name);
	}
}


void ShaderProgram::updateFromCam() {
	// Get view and projection matrices from camera
	glm::mat4 viewMatrix = camera->getViewMatrix();
	glm::mat4 projectionMatrix = camera->getProjectionMatrix();
	
	printf("we were notified from camera\n");

	// Set matrices in the shader program (pseudo-code)
	setMatrixUniform("viewMatrix", viewMatrix);
	setMatrixUniform("projectionMatrix", projectionMatrix);
}

