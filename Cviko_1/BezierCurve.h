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
    BezierCurve(const glm::mat4x3& controlPoints, float speed = 0.01f)
        : t(0.0f), speed(speed) {
        controlMatrix = glm::transpose(controlPoints);
        bezierMatrix = glm::mat4(
            glm::vec4(-1.0, 3.0, -3.0, 1.0),
            glm::vec4(3.0, -6.0, 3.0, 0.0),
            glm::vec4(-3.0, 3.0, 0.0, 0.0),
            glm::vec4(1.0, 0.0, 0.0, 0.0)
        );
    }

    void update(float deltaTime) {
		printf("t: %f\n", t);
        t += speed * deltaTime;
        if (t >= 1.0f || t <= 0.0f) {
            speed *= -1; // Oto�en� sm�ru
        }
    }

    glm::vec3 getPosition() const {
        glm::vec4 tVec(t * t * t, t * t, t, 1.0f);
        return tVec * bezierMatrix * controlMatrix;
    }

    glm::mat4 getModelMatrix(float deltaTime) {
        update(deltaTime);
        glm::vec3 position = getPosition();
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
        return modelMatrix;
    }
};
