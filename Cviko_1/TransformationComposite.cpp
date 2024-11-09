#include "TransformationComposite.h"

void TransformationComposite::transform(glm::mat4& matrix, float deltaTime)
{
    for (auto& transformation : this->childs)
    {
        transformation->transform(matrix, deltaTime);
    }
}

void TransformationComposite::AddTransformation(TransformationComponent* transformation)
{
    this->childs.push_back(transformation);
}

void TransformationComposite::clearTransformations()
{
    childs.clear();
}