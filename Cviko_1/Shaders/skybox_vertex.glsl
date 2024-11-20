#version 400

uniform mat4 viewMatrix;       // Matice pohledu kamery
uniform mat4 projectionMatrix; // Projek�n� matice
uniform bool followsCamera;    // P�ep�na� pro sledov�n� kamery

layout(location = 0) in vec3 in_Position; // Vstupn� pozice vrchol�

out vec3 texCoord; // V�stupn� texturov� sou�adnice pro fragment shader

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

    // V�po�et kone�n� pozice vrchol�
    gl_Position = projectionMatrix * view * vec4(in_Position * 50.0, 1.0f); // Zv�t�en� skyboxu
    texCoord = in_Position; // P�ed�n� p�vodn�ch sou�adnic
}
