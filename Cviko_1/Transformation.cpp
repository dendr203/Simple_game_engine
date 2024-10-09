#include "Transformation.h"

Transformation::Transformation() {
    modelMatrix = glm::mat4(1.0f);
}

Transformation::~Transformation() {}

void Transformation::translate(float x, float y, float z) {
    modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y, z));
}

void Transformation::rotate(float angle, float x, float y, float z) {
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(x, y, z));
}

void Transformation::scale(float x, float y, float z) {
    modelMatrix = glm::scale(modelMatrix, glm::vec3(x, y, z));
}

glm::mat4 Transformation::getModelMatrix() const {
    return modelMatrix;
}

void Transformation::clearModelMatrix()
{
	modelMatrix = glm::mat4(1.0f);
}