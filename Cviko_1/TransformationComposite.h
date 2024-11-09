#pragma once
#include "TransformationComponent.h"
#include <vector>
#include <glm/ext/vector_float3.hpp>


class TransformationComposite : public TransformationComponent {
public:
    
    void transform(glm::mat4& modelMatrix, float deltaTime) override;
    void AddTransformation(TransformationComponent* transformation);

    void clearTransformations();

private:
    std::vector<TransformationComponent*> childs;
};
