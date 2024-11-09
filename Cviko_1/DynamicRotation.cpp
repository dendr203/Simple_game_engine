#include "DynamicRotation.h"

DynamicRotation::DynamicRotation(float speed, glm::vec3 axis)
    : speed(speed), axis(axis), currentAngle(0.0f) {}


float DynamicRotation::update(float deltaTime)
{
    return currentAngle += speed * deltaTime;
}

void DynamicRotation::transform(glm::mat4& modelMatrix, float deltaTime)
{
    modelMatrix = glm::rotate(modelMatrix, glm::radians(update(deltaTime)), axis);
}