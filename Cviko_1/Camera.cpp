#include "Camera.h"

Camera::Camera(float _aspectRatio) : position(), front(), up(), movementSpeed(0.0f),
	fov(0.0f), yaw(0.0f), pitch(0.0f), sensitivity(0.0f), aspectRatio(_aspectRatio), viewMatrix(), projectionMatrix(), right()
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
	updateProjectionMatrix();
	updateCameraVectors();
}

void Camera::move(const glm::vec3& direction)
{
	position += direction * movementSpeed;
	updateViewMatrix();
}

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

glm::vec3 Camera::getCameraPosition()
{
	return position;
}

glm::mat4 Camera::getViewMatrix(){
	return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix(){
	return projectionMatrix;
}

glm::vec3 Camera::getFront() {
	return front;
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



void Camera::updateAspectRatio(float _aspectRatio)
{
	aspectRatio = _aspectRatio;
	updateProjectionMatrix();
}

void Camera::updateProjectionMatrix()
{
	projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
	updateObserversProjection();
}

void Camera::updateObserversProjection()
{
	for (Observer* obs : observers)
	{
		ShaderProgram* shaderProgram = (ShaderProgram*)obs;
		shaderProgram->setProjectionMatrix();
	}
}


void Camera::updateViewMatrix()
{
	viewMatrix = glm::lookAt(position, position + front, up);
	notifyObservers();
}


void Camera::addObserver(Observer* observer) {
	observers.push_back(observer);
	updateViewMatrix();

	ShaderProgram* shader_prg = (ShaderProgram*) observer;
	shader_prg->setProjectionMatrix();
}

void Camera::removeObserver(Observer* observer) {
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Camera::notifyObservers() {
	for (Observer* obs : observers)
	{
		ShaderProgram* shaderProgram = dynamic_cast<ShaderProgram*>(obs);
		if (shaderProgram)
		{
			shaderProgram->updateFromSubject();
		}
		else
		{
			printf("ShaderProgram not found!!!\n");
		}
		
	}
}	

void Camera::clearLinkShaders() {
	observers.clear();
}

