#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>
#include "Observer.h"
#include "Subject.h"
#include "ShaderProgram.h"

class ShaderProgram;
class Light : public Subject
{
public:
    Light(glm::vec3 position, glm::vec3 color, glm::vec4 ambient);

    // Settery pro nastavení atributù svìtla
    void setColor(const glm::vec3& color);
    void setPosition(const glm::vec3& position);
	void setAmbient(const glm::vec4& ambient);

    glm::vec3 getPosition();
    glm::vec3 getColor();
    glm::vec4 getAmbient();

    // Pøidat/odebrat pozorovatele
    void addObserver(Observer* observer) override;
    void removeObserver(Observer* observer) override;
    void notifyObservers() override;

private:
    glm::vec3 position;
    glm::vec3 color;      
    glm::vec4 ambient;

    std::vector<Observer*> observers;
};
