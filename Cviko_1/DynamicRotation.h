#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

#include "TransformationComponent.h"

class DynamicRotation : public TransformationComponent {
public:
    DynamicRotation(float speed, glm::vec3 axis);

    void update(float deltaTime);

    void transform(glm::mat4& modelMatrix) override;

private:
    float speed;            // Rychlost rotace v stupních za sekundu
    glm::vec3 axis;         // In which axis we are rotating
    float currentAngle;     

};

