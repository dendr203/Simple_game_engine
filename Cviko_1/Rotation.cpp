#include "Rotation.h"

Rotation::Rotation(float angle, glm::vec3 value) : rotationAngle(angle), rotationAxis(value) {}


void Rotation::transform(glm::mat4& modelMatrix)
{
    modelMatrix = glm::rotate(modelMatrix, rotationAngle, rotationAxis);
}