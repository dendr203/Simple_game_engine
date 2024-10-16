#include "Camera.h"
#include "Shader.h"


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

