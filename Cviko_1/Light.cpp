#include "Light.h"
#include "ShaderProgram.h"

Light::Light(glm::vec3 color) : color(color) {}


LightType Light::getLightType() {
    return lightType;
}

glm::vec3 Light::getColor() {
    return color;
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