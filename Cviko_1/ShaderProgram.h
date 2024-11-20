#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "Observer.h"
#include "Camera.h"
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "Material.h"


#include "ShaderLoader.h"

class Light;
class Camera;
class ShaderProgram : public Observer, public ShaderLoader
{
public:
	ShaderProgram(Camera* camera);
	~ShaderProgram();

	void init_shader(const char* vertex_shader_str, const char* fragment_shader_str);
	void use_shader();
	void unuse_Shader();
	void addLight(Light* light);
	

	void setModelMatrix(const glm::mat4& model_matrix);
	void setViewMatrix();
	void setProjectionMatrix();

	void setObjectColor(const glm::vec4& obj_color);
	void setMaterial(Material material);

	void updateFromSubject() override;
	

	void setTexture(int unitID, float tex_scale);
	void unsetTexture();
	void setSkyboxTexture(bool followCamera);

private:
	Camera* camera;
	std::vector<Light*> lights;

	GLuint getLocation(const char* name);

	void setLights();


	void setUniformLocation(const char* name, const glm::mat4& matrix);
	void setUniformLocation(const char* name, const glm::vec3& vector);
	void setUniformLocation(const char* name, const glm::vec4& vector);
	void setUniformLocation(const char* name, float _float);
	void setUniformLocation(const char* name, int _int);
	
	
};

