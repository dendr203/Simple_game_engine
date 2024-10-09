#include "Shader.h"


Shader::Shader() {}

void Shader::init_shader(GLenum type, const char* shader_string)
{
	shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &shader_string, NULL);
	glCompileShader(shader_id);
}

GLuint Shader::GetShader()
{
	return shader_id;
}