#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Subject.h"
#include "Observer.h"
#include "ShaderProgram.h"
#include <vector>

class ShaderProgram;
class Camera : public Subject
{
public:
    Camera(float _aspectRatio);

    void updateAspectRatio(float _aspectRatio);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    void processMouseMovement(float xoffset, float yoffset);
    void setCamera(glm::vec3 position, glm::vec3 front, glm::vec3 up,
        float speed, float _fov, float _yaw, float _pitch, float _sensitivity);

    
    void moveForward();
    void moveBackwards();
    void moveLeft();
    void moveRight();

    void addObserver(Observer* observer) override;
	void removeObserver(Observer* observer) override;
    void notifyObservers() override;
    void clearLinkShaders() override;

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;
    float sensitivity;
    float movementSpeed;
    float fov;
    float aspectRatio;

    
    
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    void move(const glm::vec3& direction);
    void updateCameraVectors();
    void updateProjectionMatrix();
    void updateViewMatrix();

    void updateObserversProjection();

    std::vector<Observer*> observers;
};

