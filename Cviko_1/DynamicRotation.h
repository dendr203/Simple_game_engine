#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

#include "TransformationComponent.h"

class DynamicRotation : public  TransformationComponent{
public:
    DynamicRotation(float speed, glm::vec3 axis);

    float update(float deltaTime);

    void transform(glm::mat4& modelMatrix, float deltaTime) override;


private:
    float speed;
    float currentAngle;
    glm::vec3 axis;
};

