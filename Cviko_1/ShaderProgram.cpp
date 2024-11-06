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


void ShaderProgram::addLight(Light* light)
{
	lights.push_back(light);
}

void ShaderProgram::setLights()
{

	int counter = 0;
	for (Light* light : lights)
	{
		// Set number of lights if the uniform exists in the shader
		GLint numberOfLightsLoc = getLocation("numberOfLights");

		if (numberOfLightsLoc != -1) {

			setUniformLocation("cameraPosition", camera->getCameraPosition());
			glProgramUniform1i(shaderProgramID, numberOfLightsLoc, lights.size());


			std::string positionName = "lights[" + std::to_string(counter) + "].position";
			GLint lightPositionLocation = getLocation(positionName.c_str());
			if (lightPositionLocation != -1)
			{
				setUniformLocation(positionName.c_str(), light->getPosition());
			}


			std::string l_colorName = "lights[" + std::to_string(counter) + "].lightC";
			GLint lightColorLocation = getLocation(l_colorName.c_str());
			if (lightColorLocation != -1)
			{
				setUniformLocation(l_colorName.c_str(), light->getColor());
			}


			std::string ambientName = "lights[" + std::to_string(counter) + "].ambient";
			GLint lightAmbientLocation = getLocation(ambientName.c_str());
			if (lightAmbientLocation != -1)
			{
				setUniformLocation(ambientName.c_str(), light->getAmbient());
			}


			std::string shininessName = "lights[" + std::to_string(counter) + "].shininess";
			GLint lightShininessLocation = getLocation(shininessName.c_str());
			if (lightShininessLocation != -1)
			{
				setUniformLocation(shininessName.c_str(), light->getShinines());
			}


			std::string constantName = "lights[" + std::to_string(counter) + "].constant";
			GLint lightConstantLocation = getLocation(constantName.c_str());
			if (lightConstantLocation != -1)
			{
				setUniformLocation(constantName.c_str(), 1.0f);
			}


			std::string linearName = "lights[" + std::to_string(counter) + "].linear";
			GLint lightLinearLocation = getLocation(linearName.c_str());
			if (lightLinearLocation != -1)
			{
				setUniformLocation(linearName.c_str(), 0.09f);
			}


			std::string quadraticName = "lights[" + std::to_string(counter) + "].quadratic";
			GLint lightquadraticLocation = getLocation(quadraticName.c_str());
			if (lightquadraticLocation != -1)
			{
				setUniformLocation(quadraticName.c_str(), 0.07f);
			}
			
		}
		else
		{
			GLint lightPositionLocation = getLocation("lightPosition");
			if (lightPositionLocation != -1)
			{
				setLightPosition(light);
			}

			GLint lightColorLocation = getLocation("lightColor");
			if (lightColorLocation != -1)
			{
				setLightColor(light); //maybe not now every time
			}

			GLint ambientLightLocation = getLocation("ambientLight");
			if (ambientLightLocation != -1)
			{
				setAmbient(light);
			}

			GLint shininessLocation = getLocation("shininess");
			if (shininessLocation != -1) {
				setShinines(light);
			}
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




