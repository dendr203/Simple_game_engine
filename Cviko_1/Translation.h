#pragma once
#include "TransformationComponent.h"
#include <glm/gtc/matrix_transform.hpp>

class Translation : public TransformationComponent {
public:
    Translation(float x, float y, float z);

    void apply(glm::mat4& modelMatrix) override;

private:
    glm::vec3 translationVector;
};
