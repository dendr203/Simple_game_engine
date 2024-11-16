#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight(glm::vec3 direction, glm::vec3 color);

	glm::vec3 getDirection();

private:
	glm::vec3 direction;
};

