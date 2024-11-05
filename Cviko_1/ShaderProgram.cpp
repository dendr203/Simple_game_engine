#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Camera* _camera, Light* _light) : camera(_camera), light(_light) {}

ShaderProgram::~ShaderProgram()
{
	deleteShader();
}

void ShaderProgram::init_shader(const char* vertexFile, const char* fragmentFile)
{
	//ShaderLoader* shader_loader = new ShaderLoader(vertexFile, fragmentFile, &shaderProgramID);
	//delete(shader_loader);
	
	this->shaderProgramID = loadShader(vertexFile, fragmentFile);

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



void ShaderProgram::setModelMatrix(const glm::mat4& model_matrix)
{
	setUniformLocation("modelMatrix", model_matrix);
}

void ShaderProgram::setViewMatrix()
{
	setUniformLocation("viewMatrix", camera->getViewMatrix());
}

void ShaderProgram::setProjectionMatrix()
{
	setUniformLocation("projectionMatrix", camera->getProjectionMatrix());
}

void ShaderProgram::setObjectColor(const glm::vec4& color)
{
	setUniformLocation("objectColor", color);
}

void ShaderProgram::setLightPosition()
{
	setUniformLocation("lightPosition", light->getPosition());
}

void ShaderProgram::setLightColor()
{
	setUniformLocation("lightColor", light->getColor());
}

void ShaderProgram::setAmbient()
{
	setUniformLocation("ambientLight", light->getAmbient());
}

void ShaderProgram::setShinines()
{
	setUniformLocation("shininess", light->getShinines());
}

void ShaderProgram::updateFromSubject() {
	//printf("we were notified from camera\n");


	setViewMatrix();

	/*
	GLint lightPositionLocation = getLocation("lightPosition");
	if (lightPositionLocation != -1)
	{
		setLightPosition();
	}
	
	GLint lightColorLocation = getLocation("lightColor");
	if (lightColorLocation != -1)
	{
		setLightColor();
	}
	
	GLint ambientLightLocation = getLocation("ambientLight");
	if (ambientLightLocation != -1)
	{
		setAmbient();
	}
	
	GLint shininessLocation = getLocation("shininess");
	if (shininessLocation != -1) {
		setShinines();
	}
	*/
}




