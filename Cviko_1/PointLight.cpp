#include "PointLight.h"

PointLight::PointLight(glm::vec3 position, glm::vec3 color, float constant, float linear, float quadratic)
	:Light(color), position(position), constant(constant), linear(linear), quadratic(quadratic)
{
	lightType = POINT;
}

float PointLight::getConstant() {
	return constant;
}

float PointLight::getLinear() {
	return linear;
}

float PointLight::getQuadratic() {
	return quadratic;
}

glm::vec3 PointLight::getPosition() {
	return position;
}