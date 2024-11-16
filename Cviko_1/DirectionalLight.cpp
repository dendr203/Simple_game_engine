#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color)
	:Light(color), direction(direction)
{
	lightType = DIRECTIONAL;
}

glm::vec3 DirectionalLight::getDirection() {
	return direction;
}