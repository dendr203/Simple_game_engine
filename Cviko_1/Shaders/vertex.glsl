#version 400

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;


out vec3 worldNormal;
out vec4 fragPosition;
out vec3 viewDirection;



void main(void) {
   fragPosition = modelMatrix * vec4(in_Position, 1.0f);

   mat4 normal = transpose(inverse(modelMatrix));
   worldNormal = normalize(vec3(normal * vec4(in_Normal, 0.0)));

   gl_Position = projectionMatrix * viewMatrix * fragPosition;

   viewDirection = normalize(vec3(inverse(viewMatrix)[3]) - vec3(fragPosition));
};