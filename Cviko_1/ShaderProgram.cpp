#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Camera* _camera, Light* _light) : camera(_camera), light(_light) {}

ShaderProgram::~ShaderProgram()
{
	deleteShader();
}

void ShaderProgram::init_shader(const char* vertexFile, const char* fragmentFile)
{
	ShaderLoader* shader_loader = new ShaderLoader(vertexFile, fragmentFile, &shaderProgramID);
	delete(shader_loader);


	GLint status;
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgramID, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		exit(EXIT_FAILURE);
	}


	if (shaderProgramID == 0) {
		fprintf(stderr, "Failed to load shaders from files: %s, %s\n", vertexFile, fragmentFile);
		exit(EXIT_FAILURE);
	}

	printf("Shader program loaded successfully.\n");
	
}



void ShaderProgram::use_shader()
{
	glUseProgram(shaderProgramID);
}



GLuint ShaderProgram::getLocation(const char* name)
{
	return glGetUniformLocation(shaderProgramID, name);
}


void ShaderProgram::setUniformLocation(const char* name, const glm::mat4& matrix) {
	GLuint location = getLocation(name);
	if (location != -1) {
		glProgramUniformMatrix4fv(shaderProgramID, location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	else {
		printf("Uniform %s not found!\n", name);
	}
}

void ShaderProgram::setUniformLocation(const char* name, const glm::vec3& vector) {
	GLuint location = getLocation(name);
	if (location != -1) {
		glProgramUniform3f(shaderProgramID, location, vector.x, vector.y, vector.z);
	}
	else {
		printf("Uniform %s not found!\n", name);
	}
}

void ShaderProgram::setUniformLocation(const char* name, const glm::vec4& vector) {
	GLuint location = getLocation(name);
	if (location != -1) {
		glProgramUniform4f(shaderProgramID, location, vector.x, vector.y, vector.z, vector.w);
	}
	else {
		printf("Uniform %s not found!\n", name);
	}
}

void ShaderProgram::setUniformLocation(const char* name, float _float) {
	GLuint location = getLocation(name);
	if (location != -1) {
		glProgramUniform1f(shaderProgramID, location, _float);
	}
	else {
		printf("Uniform %s not found!\n", name);
	}
}

void ShaderProgram::updateFromSubject() {
	//printf("we were notified from camera\n");


	setUniformLocation("viewMatrix", camera->getViewMatrix());


	GLint lightPositionLocation = getLocation("lightPosition");
	if (lightPositionLocation != -1)
	{
		setUniformLocation("lightPosition", light->getPosition());
	}
	
	GLint lightColorLocation = getLocation("lightColor");
	if (lightColorLocation != -1)
	{
		setUniformLocation("lightColor", light->getColor());
	}
	
	GLint ambientLightLocation = getLocation("ambientLight");
	if (ambientLightLocation != -1)
	{
		setUniformLocation("ambientLight", light->getAmbient());
	}
	

	GLint shininessLocation = getLocation("shininess");
	if (shininessLocation != -1) {
		setUniformLocation("shininess", light->getShinines());
	}
}


void ShaderProgram::setProjectionMatrix()
{
	setUniformLocation("projectionMatrix", camera->getProjectionMatrix());
}

