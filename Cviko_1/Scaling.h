#pragma once
#include "TransformationComponent.h"
#include <glm/gtc/matrix_transform.hpp>

class Scaling : public TransformationComponent {
public:
    Scaling(glm::vec3 _scaleVector);

    void transform(glm::mat4& modelMatrix, float deltaTime) override;

private:
    glm::vec3 scaleVector;
};
