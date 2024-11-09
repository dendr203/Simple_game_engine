#include "Scaling.h"

Scaling::Scaling(glm::vec3 _scaleVector) : scaleVector(_scaleVector) {}

void Scaling::transform(glm::mat4& modelMatrix, float deltaTime)
{
    modelMatrix = glm::scale(modelMatrix, scaleVector);
}