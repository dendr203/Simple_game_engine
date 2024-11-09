#pragma once
#include <glm/glm.hpp>

class TransformationComponent {
public:
    virtual ~TransformationComponent() {}
    virtual void transform(glm::mat4& modelMatrix, float deltaTime) = 0;
};
