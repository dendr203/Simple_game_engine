#version 400

uniform mat4 viewMatrix;       
uniform mat4 projectionMatrix;
uniform bool followsCamera;    // Pøepínaè pro sledování kamery

layout(location = 0) in vec3 in_Position;

out vec3 texCoord;

void main(void) {
    mat4 view;
    float scale = 1.f;

    if (followsCamera)
    {
        view = mat4(mat3(viewMatrix));      // Ignorujeme z-tovou souøadnici kamery
    }
    else
    {
        view = viewMatrix;
        scale = 50.0f;                      // Zvìtšení skyboxu pro lepší pohled, když sledujeme kameru
    }

    gl_Position = projectionMatrix * view * vec4(in_Position * scale, 1.0f);
    texCoord = in_Position; // Pøedání pùvodních souøadnic
}
