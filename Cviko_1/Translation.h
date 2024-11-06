#pragma once
#include "TransformationComponent.h"
#include <glm/gtc/matrix_transform.hpp>

class Translation : public TransformationComponent {
public:
    Translation(glm::vec3 _translationVector);

    void transform(glm::mat4& modelMatrix) override;

private:
    glm::vec3 translationVector;
};
