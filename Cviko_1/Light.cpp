#include "Light.h"
#include "ShaderProgram.h"

Light::Light(glm::vec3 color) : color(color) {}


LightType Light::getLightType() {
    return lightType;
}

glm::vec3 Light::getColor() {
    return color;
}





