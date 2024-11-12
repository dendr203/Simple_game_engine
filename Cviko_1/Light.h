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
    Light(int light_type, glm::vec3 position, glm::vec3 color, glm::vec4 ambient, float shinines);

    // Settery not in work now
    void setColor(const glm::vec3& color);
    void setPosition(const glm::vec3& position);
	void setAmbient(const glm::vec4& ambient);

	int getLightType();
    glm::vec3 getPosition();
    glm::vec3 getColor();
    glm::vec4 getAmbient();
    float getShinines();

	glm::vec3 getDirection();
    float getCutoff();
	float getOuterCutoff();

    
    void addObserver(Observer* observer) override;
    void removeObserver(Observer* observer) override;
    void notifyObservers() override;
    void clearLinkShaders() override;

private:
    int light_type;
    glm::vec3 position;
    glm::vec3 color;      
    glm::vec4 ambient;
    float shinines;

    std::vector<Observer*> observers;
};
