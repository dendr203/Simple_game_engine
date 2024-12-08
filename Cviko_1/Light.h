#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>



enum LightType { POINT, DIRECTIONAL, SPOTLIGHT };



class Light
{
public:
    Light(glm::vec3 color);

    virtual ~Light() = default;

    LightType getLightType();
    glm::vec3 getColor();


protected:
    LightType lightType;
    glm::vec3 color;
};