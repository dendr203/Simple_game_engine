#include "Shader.h"


Shader::Shader() : shader_id(-1) {}

void Shader::init_shader(GLenum type, const char* shader_string)
{
	shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &shader_string, NULL);
	glCompileShader(shader_id);
}
//z toho pan nemec nebude nadseny
GLuint Shader::GetShader()
{
	return shader_id;
}
