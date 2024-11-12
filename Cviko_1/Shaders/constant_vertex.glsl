#version 400

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;

out vec4 fragPosition;
out vec3 worldNormal;

void main(void) {
    fragPosition = modelMatrix * vec4(in_Position, 1.0f); // World coordinates
    mat4 normal = transpose(inverse(modelMatrix));
    worldNormal = normalize(vec3(normal * vec4(in_Normal, 0.0))); // World normal
    gl_Position = projectionMatrix * viewMatrix * fragPosition; // Final transformed position
}
