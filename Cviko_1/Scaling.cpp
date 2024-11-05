#include "Scaling.h"

Scaling::Scaling(float x, float y, float z) : scaleVector(x, y, z) {}

void Scaling::transform(glm::mat4& modelMatrix)
{
    modelMatrix = glm::scale(modelMatrix, scaleVector);
}