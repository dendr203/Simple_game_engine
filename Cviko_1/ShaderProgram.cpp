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




void ShaderProgram::setMatrixUniform(const char* name, const glm::mat4& matrix) {
	GLuint location = glGetUniformLocation(shaderProgramID, name);
	if (location != -1) {
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	else {
		printf("Uniform %s not found!\n", name);
	}
}

void ShaderProgram::setVector3Uniform(const char* name, const glm::vec3& vector) {
	GLuint location = glGetUniformLocation(shaderProgramID, name);
	if (location != -1) {
		glUniform3fv(location, 1, glm::value_ptr(vector));
	}
	else {
		printf("Uniform %s not found!\n", name);
	}
}

void ShaderProgram::setVector4Uniform(const char* name, const glm::vec4& vector) {
	GLuint location = glGetUniformLocation(shaderProgramID, name);
	if (location != -1) {
		glUniform4fv(location, 1, glm::value_ptr(vector));
	}
	else {
		printf("Uniform %s not found!\n", name);
	}
}

void ShaderProgram::setFloatUniform(const char* name, float _float) {
	GLuint location = glGetUniformLocation(shaderProgramID, name);
	if (location != -1) {
		glUniform1f(location, _float);
	}
	else {
		printf("Uniform %s not found!\n", name);
	}
}

void ShaderProgram::updateFromSubject() {
	//printf("we were notified from camera\n");

	use_shader();
	setMatrixUniform("viewMatrix", camera->getViewMatrix());


	GLint lightPositionLocation = glGetUniformLocation(shaderProgramID, "lightPosition");
	if (lightPositionLocation != -1)
	{
		setVector3Uniform("lightPosition", light->getPosition());
	}
	
	GLint lightColorLocation = glGetUniformLocation(shaderProgramID, "lightColor");
	if (lightColorLocation != -1)
	{
		setVector3Uniform("lightColor", light->getColor());
	}
	
	GLint ambientLightLocation = glGetUniformLocation(shaderProgramID, "ambientLight");
	if (ambientLightLocation != -1)
	{
		setVector4Uniform("ambientLight", light->getAmbient());
	}
	

	GLint shininessLocation = glGetUniformLocation(shaderProgramID, "shininess");
	if (shininessLocation != -1) {
		setFloatUniform("shininess", light->getShinines());
	}
}


void ShaderProgram::setProjectionMatrix()
{
	use_shader();
	setMatrixUniform("projectionMatrix", camera->getProjectionMatrix());
}

