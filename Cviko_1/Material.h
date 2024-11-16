#pragma once
#include <glm/glm.hpp>

class Material {
public:
    Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);

    glm::vec3 getAmbient();
    glm::vec3 getDiffuse();
    glm::vec3 getSpecular();
    float getShininess();

private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};
