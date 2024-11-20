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


			//set for every light
			std::string l_colorName = "lights[" + std::to_string(counter) + "].lightC";
			setUniformLocation(l_colorName.c_str(), light->getColor());

			int type = static_cast<int>(light->getLightType());
			std::string lightType = "lights[" + std::to_string(counter) + "].type";
			setUniformLocation(lightType.c_str(), type);

			if (light->getLightType() == POINT)
			{
				PointLight* pointlight = dynamic_cast<PointLight*>(light);

				std::string positionName = "lights[" + std::to_string(counter) + "].position";
				setUniformLocation(positionName.c_str(), pointlight->getPosition());

				std::string constantName = "lights[" + std::to_string(counter) + "].constant";
				setUniformLocation(constantName.c_str(), pointlight->getConstant());

				std::string linearName = "lights[" + std::to_string(counter) + "].linear";
				setUniformLocation(linearName.c_str(), pointlight->getLinear());

				std::string quadraticName = "lights[" + std::to_string(counter) + "].quadratic";
				setUniformLocation(quadraticName.c_str(), pointlight->getQuadratic());
				//0.1 0.3 0.032
			}
			else if (light->getLightType() == DIRECTIONAL)
			{
				DirectionalLight* directionallight = dynamic_cast<DirectionalLight*>(light);

				std::string directionName = "lights[" + std::to_string(counter) + "].direction";
				setUniformLocation(directionName.c_str(), directionallight->getDirection());
			}
			else if (light->getLightType() == SPOTLIGHT)
			{
				SpotLight* spotlight = dynamic_cast<SpotLight*>(light);

				if (spotlight->is_attached() == 1)
				{
					std::string positionName = "lights[" + std::to_string(counter) + "].position";
					setUniformLocation(positionName.c_str(), camera->getCameraPosition());

					std::string directionName = "lights[" + std::to_string(counter) + "].direction";
					setUniformLocation(directionName.c_str(), camera->getFront());
				}
				else
				{
					std::string positionName = "lights[" + std::to_string(counter) + "].position";
					setUniformLocation(positionName.c_str(), spotlight->getPosition());

					std::string directionName = "lights[" + std::to_string(counter) + "].direction";
					setUniformLocation(directionName.c_str(), spotlight->getDirection());
				}

				std::string cutoffName = "lights[" + std::to_string(counter) + "].cutoff";
				setUniformLocation(cutoffName.c_str(), spotlight->getCutoff());

				std::string outerCutoffName = "lights[" + std::to_string(counter) + "].outerCutoff";
				setUniformLocation(outerCutoffName.c_str(), spotlight->getOuterCutoff());
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
		glUseProgram(shaderProgramID);
		glProgramUniformMatrix4fv(shaderProgramID, location, 1, GL_FALSE, glm::value_ptr(matrix));
		glUseProgram(0);
	}
}

void ShaderProgram::setUniformLocation(const char* name, const glm::vec3& vector) {
	GLuint location = getLocation(name);
	if (location >= 0)
	{
		glUseProgram(shaderProgramID);
		glProgramUniform3f(shaderProgramID, location, vector.x, vector.y, vector.z);
		glUseProgram(0);
	}
}

void ShaderProgram::setUniformLocation(const char* name, const glm::vec4& vector) {
	GLuint location = getLocation(name);
	if (location >= 0)
	{
		glUseProgram(shaderProgramID);
		glProgramUniform4f(shaderProgramID, location, vector.x, vector.y, vector.z, vector.w);
		glUseProgram(0);
	}
}

void ShaderProgram::setUniformLocation(const char* name, float _float) {
	GLuint location = getLocation(name);
	if (location >= 0)
	{
		glUseProgram(shaderProgramID);
		glProgramUniform1f(shaderProgramID, location, _float);
		glUseProgram(0);
	}
}

void ShaderProgram::setUniformLocation(const char* name, int _int) {
	GLuint location = getLocation(name);
	if (location >= 0)
	{
		glUseProgram(shaderProgramID);
		glProgramUniform1i(shaderProgramID, location, _int);
		glUseProgram(0);
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

void ShaderProgram::setMaterial(Material material)
{
	setUniformLocation("material.ambient", material.getAmbient());
	setUniformLocation("material.diffuse", material.getDiffuse());
	setUniformLocation("material.specular", material.getSpecular());
	setUniformLocation("material.shininess", material.getShininess());
}

void ShaderProgram::setTexture(int unitID, float tex_scale)
{
	setUniformLocation("useTexture", 1);
	setUniformLocation("textureScale", tex_scale);
	setUniformLocation("textureSampler", unitID);
}

void ShaderProgram::setSkyboxTexture(bool followCamera)
{
	setUniformLocation("useTexture", 1);
	setUniformLocation("textureSampler", 0);
	setUniformLocation("followsCamera", followCamera);
}

void ShaderProgram::unsetTexture()
{
	setUniformLocation("useTexture", 0);
}


void ShaderProgram::updateFromSubject()
{
	setViewMatrix();
	setLights();
}




