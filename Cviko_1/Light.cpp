#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color, glm::vec4 ambient, float _shinines)
    : position(position), color(color), ambient(ambient), shinines(_shinines) {}

void Light::setPosition(const glm::vec3& newPosition) {
    position = newPosition;
    notifyObservers();
}

void Light::setColor(const glm::vec3& newColor) {
    color = newColor;
    notifyObservers();
}

void Light::setAmbient(const glm::vec4& newAmbient) {
    ambient = newAmbient;
    notifyObservers();
}

glm::vec3 Light::getPosition() {
	return position;
}

glm::vec3 Light::getColor() {
	return color;
}

glm::vec4 Light::getAmbient() {
	return ambient;
}

float Light::getShinines() {
    return shinines;
}

void Light::addObserver(Observer* observer) {
    observers.push_back(observer);
}

void Light::removeObserver(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Light::notifyObservers() {
    for (Observer* observer : observers)
    {
        ShaderProgram* shaderProgram = dynamic_cast<ShaderProgram*>(observer);
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

void Light::clearLinkShaders() {
    observers.clear();
}
