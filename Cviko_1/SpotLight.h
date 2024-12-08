#pragma once
#include "Light.h"

#include "BezierCurve.h"

class SpotLight : public Light
{
public:
	SpotLight(int camera_attached, glm::vec3 position, glm::vec3 direction, glm::vec3 color,
		float cutoff, float outerCutoff, BezierCurve* curve = nullptr);

	glm::vec3 getPosition();
	glm::vec3 getDirection();
	float getCutoff();
	float getOuterCutoff();

	int is_attached();

private:
	glm::vec3 position;
	glm::vec3 direction;
	float cutoff;
	float outercutoff;

	int camera_attached;

	BezierCurve* curve;
};

