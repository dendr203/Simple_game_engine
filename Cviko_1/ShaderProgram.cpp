#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {}

ShaderProgram::~ShaderProgram() {}

void ShaderProgram::init_shader(const char* vertex_shader_str, const char* fragment_shader_str)
{
	Shader vertex_shader;
	vertex_shader.init_shader(GL_VERTEX_SHADER, vertex_shader_str);

	Shader fragment_shader;
	fragment_shader.init_shader(GL_FRAGMENT_SHADER, fragment_shader_str);

	shaderProgram_id = glCreateProgram();
	glAttachShader(shaderProgram_id, fragment_shader.GetShader());
	glAttachShader(shaderProgram_id, vertex_shader.GetShader());
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
	glDeleteShader(vertex_shader.GetShader());
	glDeleteShader(fragment_shader.GetShader());
}

void ShaderProgram::use_shader()
{
	glUseProgram(shaderProgram_id);
}

GLuint ShaderProgram::GetShader()
{
	return shaderProgram_id;
}


