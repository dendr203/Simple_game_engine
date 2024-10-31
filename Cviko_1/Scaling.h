#pragma once
#include "TransformationComponent.h"
#include <glm/gtc/matrix_transform.hpp>

class Scaling : public TransformationComponent {
public:
    Scaling(float x, float y, float z);

    void apply(glm::mat4& modelMatrix) override;

private:
    glm::vec3 scaleVector;
};
