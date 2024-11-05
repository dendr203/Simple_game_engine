#include "Translation.h"

Translation::Translation(float x, float y, float z) : translationVector(x, y, z) {}

void Translation::transform(glm::mat4& modelMatrix)
{
    modelMatrix = glm::translate(modelMatrix, translationVector);
}