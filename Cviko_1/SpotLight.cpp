#include "SpotLight.h"

SpotLight::SpotLight(int camera_attached, glm::vec3 position, glm::vec3 direction,
	glm::vec3 color, float cutoff, float outercutoff) :
	Light(color), camera_attached(camera_attached), position(position), direction(direction),
	cutoff(cutoff), outercutoff(outercutoff)
{
	lightType = SPOTLIGHT;
}

glm::vec3 SpotLight::getPosition() {
	return position;
}

glm::vec3 SpotLight::getDirection() {
	return direction;
}

float SpotLight::getCutoff() {
	return cutoff;
}

float SpotLight::getOuterCutoff() {
	return outercutoff;
}

int SpotLight::is_attached() {
	return camera_attached;
}