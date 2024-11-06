#version 400

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;


out vec3 worldNormal;
out vec3 fragPosition;
out vec3 viewDirection;

void main(void) {
   vec4 worldPosition = modelMatrix * vec4(in_Position, 1.0f);
   fragPosition = vec3(worldPosition);

   mat4 normalMatrix = transpose(inverse(modelMatrix));
   worldNormal = normalize(vec3(normalMatrix * vec4(in_Normal, 0.0)));

   gl_Position = projectionMatrix * viewMatrix * worldPosition;

   viewDirection = normalize(cameraPosition - vec3(worldPosition));
};