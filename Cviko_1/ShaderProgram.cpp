#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Camera* _camera, Light* _light) : shaderProgram_id(-1), shaderLoader(nullptr), camera(_camera), light(_light) {}

ShaderProgram::~ShaderProgram()
{
	shaderLoader->deleteShader();
}

/*
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
*/

void ShaderProgram::init_shader(const char* vertexFile, const char* fragmentFile)
{
	shaderLoader = new ShaderLoader(vertexFile, fragmentFile, &shaderProgram_id);

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


	if (shaderProgram_id == 0) {
		fprintf(stderr, "Failed to load shaders from files: %s, %s\n", vertexFile, fragmentFile);
		exit(EXIT_FAILURE);
	}

	printf("Shader program loaded successfully.\n");
}



void ShaderProgram::use_shader()
{
	glUseProgram(shaderProgram_id);
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

void ShaderProgram::setVector3Uniform(const char* name, const glm::vec3& vector) {
	GLuint location = glGetUniformLocation(shaderProgram_id, name);
	if (location != -1) {
		glUniform3fv(location, 1, glm::value_ptr(vector));
	}
	else {
		printf("Uniform %s not found!\n", name);
	}
}

void ShaderProgram::setVector4Uniform(const char* name, const glm::vec4& vector) {
	GLuint location = glGetUniformLocation(shaderProgram_id, name);
	if (location != -1) {
		glUniform4fv(location, 1, glm::value_ptr(vector));
	}
	else {
		printf("Uniform %s not found!\n", name);
	}
}

void ShaderProgram::setFloatUniform(const char* name, float _float) {
	GLuint location = glGetUniformLocation(shaderProgram_id, name);
	if (location != -1) {
		glUniform1f(location, _float);
	}
	else {
		printf("Uniform %s not found!\n", name);
	}
}

void ShaderProgram::updateFromCam() {
	//printf("we were notified from camera\n");

	use_shader();
	setMatrixUniform("viewMatrix", camera->getViewMatrix());
	setMatrixUniform("projectionMatrix", camera->getProjectionMatrix());


	GLint lightPositionLocation = glGetUniformLocation(shaderProgram_id, "lightPosition");
	if (lightPositionLocation != -1)
	{
		setVector3Uniform("lightPosition", light->getPosition());
	}
	
	GLint lightColorLocation = glGetUniformLocation(shaderProgram_id, "lightColor");
	if (lightColorLocation != -1)
	{
		setVector3Uniform("lightColor", light->getColor());
	}
	
	GLint ambientLightLocation = glGetUniformLocation(shaderProgram_id, "ambientLight");
	if (ambientLightLocation != -1)
	{
		setVector4Uniform("ambientLight", light->getAmbient());
	}
	

	GLint shininessLocation = glGetUniformLocation(shaderProgram_id, "shininess");
	if (shininessLocation != -1) {
		setFloatUniform("shininess", light->getShinines());
	}
}

