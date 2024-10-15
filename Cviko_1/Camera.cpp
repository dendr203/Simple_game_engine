#include "Camera.h"
#include "Shader.h"

Camera::Camera(Shader* _shader, glm::vec3 _position, float _fov, float _aspectRatio, float _nearPlane, float _farPlane)
    : shader(_shader), position(_position), fov(_fov), aspectRatio(_aspectRatio), nearPlane(_nearPlane), farPlane(_farPlane),
    front(glm::vec3(0.0f, 0.0f, -1.0f)), worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    yaw(-90.0f), pitch(0.0f), movementSpeed(2.5f), mouseSensitivity(0.1f)
{
    // Inicializujeme view a projection matici
    setViewMatrix();
    setProjectionMatrix();
}


void Camera::setViewMatrix()
{
    view_matrix = glm::lookAt(position, position + front, up);
}

void Camera::setProjectionMatrix()
{
    projection_matrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void Camera::update()
{
	//shader->setMat4("viewMatrix", view_matrix);
	//shader->setMat4("projectMatrix", projection_matrix);
}

