#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader;
class Camera
{
public:
    //Camera(Shader* _shader, glm::vec3 _position, float _fov, float _aspectRatio, float _nearPlane, float _farPlane);
    Camera(glm::vec3 startPos, glm::vec3 startFront, glm::vec3 startUp)
        : position(startPos), front(startFront), up(startUp) {}

    void move(const glm::vec3& direction, float deltaTime) {
        position += direction * deltaTime;
    }

    glm::mat4 getViewMatrix() {
        return glm::lookAt(position, position + front, up);
    }

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    void setViewMatrix(); // Nastavení pohledové matice
    void setProjectionMatrix(); // Nastavení projekèní matice

    void update(); // Aktualizace matic ve shaderu

    // Metody pro pohyb kamery
    void moveForward(float deltaTime);
    void moveBackward(float deltaTime);
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);
    void rotate(float yawOffset, float pitchOffset); // Otáèení kamery

private:
    Shader* shader;

   

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;

    glm::mat4 view_matrix;
    glm::mat4 projection_matrix;

    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;

    void updateCameraVectors(); // Aktualizace vektorù pohybu na základì yaw/pitch
};

