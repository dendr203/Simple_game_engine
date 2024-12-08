#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class BezierCurve {
private:
    glm::mat4 controlMatrix; // Matice kontrolních bodù
    glm::mat4 bezierMatrix;  // Matice pro Bézierovu interpolaci
    float t;                 // Èasový parametr
    float speed;             // Rychlost zmìny parametru

public:
    BezierCurve(const glm::mat4x3& controlPoints, float speed = 0.01f);

    void update();

    glm::vec3 getPosition();

    glm::mat4 getModelMatrix(float deltaTime);
};
