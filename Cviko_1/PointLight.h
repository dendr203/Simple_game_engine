#pragma once
#include "Light.h"


class PointLight : public Light
{
public:
	PointLight(glm::vec3 position, glm::vec3 color, float constant, float linear, float quadratic);

    glm::vec3 getPosition();
    float getConstant();
    float getLinear();
    float getQuadratic();

private:
    int light_type;
    glm::vec3 position;
    glm::vec3 color;
    float constant, linear, quadratic;
};

