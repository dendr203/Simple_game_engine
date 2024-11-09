#include "Translation.h"

Translation::Translation(glm::vec3 _translationVector) : translationVector(_translationVector) {}

void Translation::transform(glm::mat4& modelMatrix, float deltaTime)
{
    modelMatrix = glm::translate(modelMatrix, translationVector);
}