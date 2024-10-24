#version 400

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;

out vec4 ex_worldPosition;
out vec3 ex_worldNormal;

void main(void) {
    ex_worldPosition = modelMatrix * vec4(in_Position, 1.0f); // World coordinates
    mat4 normalMatrix = transpose(inverse(modelMatrix));
    ex_worldNormal = normalize(vec3(normalMatrix * vec4(in_Normal, 0.0))); // World normal
    gl_Position = projectionMatrix * viewMatrix * ex_worldPosition; // Final transformed position
}
