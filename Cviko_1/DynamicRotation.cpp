#include "DynamicRotation.h"

DynamicRotation::DynamicRotation(float speed, glm::vec3 axis)
    : speed(speed), axis(axis), currentAngle(0.0f) {}


void DynamicRotation::update(float deltaTime)
{
    currentAngle += speed * deltaTime;
}

void DynamicRotation::transform(glm::mat4& modelMatrix)
{
    modelMatrix = glm::rotate(modelMatrix, glm::radians(currentAngle), axis);
}