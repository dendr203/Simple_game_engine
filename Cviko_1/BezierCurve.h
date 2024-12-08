#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class BezierCurve {
private:
    glm::mat4 controlMatrix; // Matice kontroln�ch bod�
    glm::mat4 bezierMatrix;  // Matice pro B�zierovu interpolaci
    float t;                 // �asov� parametr
    float speed;             // Rychlost zm�ny parametru

public:
    BezierCurve(const glm::mat4x3& controlPoints, float speed = 0.01f);

    void update();

    glm::vec3 getPosition();

    glm::mat4 getModelMatrix(float deltaTime);
};
