#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float speed, float _fov, float _aspectRatio)
	: position(position), front(front), up(up), movementSpeed(speed), fov(_fov), aspectRatio(_aspectRatio), yaw(-90.0f), pitch(0.0f), sensitivity(0.08f)
{
	updateCameraVectors();
	setProjectionMatrix();
}

void Camera::move(const glm::vec3& direction)
{
	position += direction * movementSpeed;
	updateViewMatrix();
}

glm::mat4 Camera::getViewMatrix(){
	return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix(){
	return projectionMatrix;
}


void Camera::updateCameraVectors() {

	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(newFront);

	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f))); // Right vector
	up = glm::normalize(glm::cross(right, front)); // Up vector

	updateViewMatrix();
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;


	updateCameraVectors();

};


void Camera::moveForward()
{
	move(front);
}

void Camera::moveBackwards()
{
	move(-front);
}

void Camera::moveLeft()
{
	move(-glm::normalize(glm::cross(front, up)));
}

void Camera::moveRight()
{
	move(glm::normalize(glm::cross(front, up)));
}

void Camera::setProjectionMatrix()
{
	projectionMatrix = glm::perspective(fov, aspectRatio, 0.1f, 100.0f);
}

void Camera::updateViewMatrix()
{
	viewMatrix = glm::lookAt(position, position + front, up);
	notifyObservers();
}


void Camera::addObserver(ShaderProgram* shaderProgram) {
	shaderPrograms.push_back(shaderProgram);
}

void Camera::notifyObservers() {
	for (auto shaderProgram : shaderPrograms)
	{
		shaderProgram->updateFromCam();
	}
}

void Camera::clearLinkShaders() {
	shaderPrograms.clear();
}

