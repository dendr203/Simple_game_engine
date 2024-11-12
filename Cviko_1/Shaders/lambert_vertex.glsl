#version 400

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;

out vec4 fragPosition;
out vec3 worldNormal;

void main(void) {
    fragPosition = modelMatrix * vec4(in_Position, 1.0f); // Calculate world coordinates
    mat4 normal = transpose(inverse(modelMatrix));
    ex_worldNormal = normalize(vec3(normalMatrix * vec4(in_Normal, 0.0))); // Calculate world normal in world coordinates
    gl_Position = projectionMatrix * viewMatrix * ex_worldPosition;
}
