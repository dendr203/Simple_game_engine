#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>
#include "Observer.h"
#include "Subject.h"

enum LightType { POINT, DIRECTIONAL, SPOTLIGHT };


class ShaderProgram;
class Light : public Subject
{
public:
    Light(glm::vec3 color);

    virtual ~Light() = default;



	LightType getLightType();
    glm::vec3 getColor();

    
    void addObserver(Observer* observer) override;
    void removeObserver(Observer* observer) override;
    void notifyObservers() override;
    void clearLinkShaders() override;

private:
    std::vector<Observer*> observers;

protected:
    LightType lightType;
    glm::vec3 color;
};
