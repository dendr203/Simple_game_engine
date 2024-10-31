#pragma once
#include <glm/glm.hpp>

class TransformationComponent {
public:
    virtual ~TransformationComponent() {}
    virtual void apply(glm::mat4& modelMatrix) = 0;
};
