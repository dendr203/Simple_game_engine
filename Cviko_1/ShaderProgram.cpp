#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Camera* _camera) : camera(_camera) {}

ShaderProgram::~ShaderProgram()
{
	deleteShader();
}

void ShaderProgram::init_shader(const char* vertexFile, const char* fragmentFile)
{	
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

void ShaderProgram::unuse_Shader()
{
	glUseProgram(0);
}


void ShaderProgram::addLight(Light* light)
{
	lights.push_back(light);
}

void ShaderProgram::setLights()
{
	int counter = 0;
	for (Light* light : lights)
	{

			setUniformLocation("numberOfLights", (int)lights.size());

			std::string lightType = "lights[" + std::to_string(counter) + "].type";
			setUniformLocation(lightType.c_str(), light->getLightType());
			
			std::string positionName = "lights[" + std::to_string(counter) + "].position";
			setUniformLocation(positionName.c_str(), light->getPosition());	

			std::string l_colorName = "lights[" + std::to_string(counter) + "].lightC";
			setUniformLocation(l_colorName.c_str(), light->getColor());

			std::string ambientName = "lights[" + std::to_string(counter) + "].ambient";
			setUniformLocation(ambientName.c_str(), light->getAmbient());


			std::string shininessName = "lights[" + std::to_string(counter) + "].shininess";
			setUniformLocation(shininessName.c_str(), light->getShinines());


			if (light->getLightType() == 0)
			{
				std::string constantName = "lights[" + std::to_string(counter) + "].constant";
				setUniformLocation(constantName.c_str(), 1.0f);


				std::string linearName = "lights[" + std::to_string(counter) + "].linear";
				setUniformLocation(linearName.c_str(), 0.09f);


				std::string quadraticName = "lights[" + std::to_string(counter) + "].quadratic";
				setUniformLocation(quadraticName.c_str(), 0.032f);
			}
			else if (light->getLightType() == 1)
			{
				std::string directionName = "lights[" + std::to_string(counter) + "].direction";
				setUniformLocation(directionName.c_str(), light->getDirection());
			}
			else if (light->getLightType() == 2)
			{
				std::string directionName = "lights[" + std::to_string(counter) + "].direction";
				setUniformLocation(directionName.c_str(), light->getDirection());

				std::string cutoffName = "lights[" + std::to_string(counter) + "].cutoff";
				setUniformLocation(cutoffName.c_str(), light->getCutoff());

				std::string outerCutoffName = "lights[" + std::to_string(counter) + "].outerCutoff";
				setUniformLocation(outerCutoffName.c_str(), light->getOuterCutoff());
			}
		counter++;
	}
}


GLuint ShaderProgram::getLocation(const char* name)
{
	return glGetUniformLocation(shaderProgramID, name);
}


void ShaderProgram::setUniformLocation(const char* name, const glm::mat4& matrix) {
	GLuint location = getLocation(name);
	if (location >= 0)
	{
		glProgramUniformMatrix4fv(shaderProgramID, location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}

void ShaderProgram::setUniformLocation(const char* name, const glm::vec3& vector) {
	GLuint location = getLocation(name);
	if (location >= 0)
	{
		glProgramUniform3f(shaderProgramID, location, vector.x, vector.y, vector.z);
	}
}

void ShaderProgram::setUniformLocation(const char* name, const glm::vec4& vector) {
	GLuint location = getLocation(name);
	if (location >= 0)
	{
		glProgramUniform4f(shaderProgramID, location, vector.x, vector.y, vector.z, vector.w);
	}
}

void ShaderProgram::setUniformLocation(const char* name, float _float) {
	GLuint location = getLocation(name);
	if (location >= 0)
	{
		glProgramUniform1f(shaderProgramID, location, _float);
	}
}

void ShaderProgram::setUniformLocation(const char* name, int _int) {
	GLuint location = getLocation(name);
	if (location >= 0)
	{
		glProgramUniform1i(shaderProgramID, location, _int);
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

void ShaderProgram::setLightPosition(Light* light)
{
	setUniformLocation("lightPosition", light->getPosition());
}

void ShaderProgram::setLightColor(Light* light)
{
	setUniformLocation("lightColor", light->getColor());
}

void ShaderProgram::setAmbient(Light* light)
{
	setUniformLocation("ambientLight", light->getAmbient());
}

void ShaderProgram::setShinines(Light* light)
{
	setUniformLocation("shininess", light->getShinines());
}

void ShaderProgram::updateFromSubject() {
	setViewMatrix();
	setLights();
}




