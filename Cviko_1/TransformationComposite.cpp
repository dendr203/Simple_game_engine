#include "TransformationComposite.h"

void TransformationComposite::transform(glm::mat4& matrix)
{
    for (auto& transformation : this->childs)
    {
        transformation->transform(matrix);
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