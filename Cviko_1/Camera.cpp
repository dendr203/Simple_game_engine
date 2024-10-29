#include "Camera.h"

Camera::Camera(float _aspectRatio) : position(), front(), up(), movementSpeed(0.0f), 
	fov(0.0f), yaw(0.0f), pitch(0.0f), sensitivity(0.0f), aspectRatio(_aspectRatio)
{}

void Camera::setCamera(glm::vec3 _position, glm::vec3 _front, glm::vec3 _up, float speed, float _fov, float _yaw, float _pitch, float _sensitivity)
{
	position = _position;
	front = _front;
	up = _up;
	movementSpeed = speed;
	fov = _fov;
	yaw = _yaw;
	pitch = _pitch;
	sensitivity = _sensitivity;
	setProjectionMatrix();
	updateCameraVectors();
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


void Camera::addObserver(Observer* observer) {
	observers.push_back(observer);
	updateViewMatrix();
	
}

void Camera::removeObserver(Observer* observer) {
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Camera::notifyObservers() {
	for (Observer* obs : observers)
	{
		ShaderProgram* shaderProgram = dynamic_cast<ShaderProgram*>(obs);
		shaderProgram->updateFromSubject();
	}
}	

void Camera::clearLinkShaders() {
	observers.clear();
}

