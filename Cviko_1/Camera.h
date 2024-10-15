#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader;
class Camera
{
public:
    Camera(Shader* _shader, glm::vec3 _position, float _fov, float _aspectRatio, float _nearPlane, float _farPlane);

    void setViewMatrix(); // Nastaven� pohledov� matice
    void setProjectionMatrix(); // Nastaven� projek�n� matice

    void update(); // Aktualizace matic ve shaderu

    // Metody pro pohyb kamery
    void moveForward(float deltaTime);
    void moveBackward(float deltaTime);
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);
    void rotate(float yawOffset, float pitchOffset); // Ot��en� kamery

private:
    Shader* shader;

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw; // Rotace kolem osy Y (ot��en� doleva/doprava)
    float pitch; // Rotace kolem osy X (ot��en� nahoru/dol�)

    float movementSpeed;
    float mouseSensitivity;

    glm::mat4 view_matrix;
    glm::mat4 projection_matrix;

    float fov; // Zorn� �hel
    float aspectRatio;
    float nearPlane;
    float farPlane;

    void updateCameraVectors(); // Aktualizace vektor� pohybu na z�klad� yaw/pitch
};

