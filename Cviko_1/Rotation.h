#pragma once
#include "TransformationComponent.h"
#include <glm/gtc/matrix_transform.hpp>

class Rotation : public TransformationComponent {
public:
    Rotation(float angle, glm::vec3 value);

    void transform(glm::mat4& modelMatrix) override;

private:
    float rotationAngle;
    glm::vec3 rotationAxis;
};
