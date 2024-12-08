#include "BezierCurve.h"


BezierCurve::BezierCurve(const glm::mat4x3& controlPoints, float speed)
    : t(0.0f), speed(speed)
{
    controlMatrix = glm::transpose(controlPoints);
    bezierMatrix = glm::mat4(
        glm::vec4(-1.0, 3.0, -3.0, 1.0),
        glm::vec4(3.0, -6.0, 3.0, 0.0),
        glm::vec4(-3.0, 3.0, 0.0, 0.0),
        glm::vec4(1.0, 0.0, 0.0, 0.0)
    );
}

//fixed time
//když jsem mìl dynamický podle snímkù, køivka mi odjela pøi dlouhé prodlevì (pøesun okna, atd...)
const float fixedDeltaTime = 1.0f / 60.0f; // 60 FPS

void BezierCurve::update()
{
    t += speed * fixedDeltaTime;
    if (t >= 1.0f || t <= 0.0f)
    {
        speed *= -1; // change direction
    }
}

glm::vec3 BezierCurve::getPosition()
{
    update();
    glm::vec4 tVec(t * t * t, t * t, t, 1.0f);
    return tVec * bezierMatrix * controlMatrix;
}


glm::mat4 BezierCurve::getModelMatrix(float deltaTime)
{
    glm::vec3 position = getPosition();
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
    return modelMatrix;
}