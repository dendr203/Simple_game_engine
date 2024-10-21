#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"
#include <vector>

class ShaderProgram;
class Camera
{
public:
    //Camera(Shader* _shader, glm::vec3 _position, float _fov, float _aspectRatio, float _nearPlane, float _farPlane);
    Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up,
        float speed, float _fov, float _aspectRatio, float _yaw, float _pitch, float _sensitivity);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    void processMouseMovement(float xoffset, float yoffset);

    
    void moveForward();
    void moveBackwards();
    void moveLeft();
    void moveRight();

    void addObserver(ShaderProgram* shaderProgram);
    void notifyObservers();

    void clearLinkShaders();

private:
    Shader* shader;

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
    void setProjectionMatrix();
    void updateViewMatrix();


    std::vector<ShaderProgram*> shaderPrograms; // List of observers
};

