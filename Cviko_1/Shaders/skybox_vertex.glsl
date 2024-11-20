#version 400

uniform mat4 viewMatrix;       // Matice pohledu kamery
uniform mat4 projectionMatrix; // Projekèní matice
uniform bool followsCamera;    // Pøepínaè pro sledování kamery

layout(location = 0) in vec3 in_Position; // Vstupní pozice vrcholù

out vec3 texCoord; // Výstupní texturové souøadnice pro fragment shader

void main(void) {
    mat4 view;

    if (followsCamera)
    {
        view = mat4(mat3(viewMatrix));
    }
    else
    {
        view = viewMatrix;
    }

    // Výpoèet koneèné pozice vrcholù
    gl_Position = projectionMatrix * view * vec4(in_Position * 50.0, 1.0f); // Zvìtšení skyboxu
    texCoord = in_Position; // Pøedání pùvodních souøadnic
}
