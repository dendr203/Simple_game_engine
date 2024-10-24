#version 400

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightPosition;

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;

out vec4 ex_worldPosition;
out vec3 ex_worldNormal;
out vec3 ex_lightDirection;
out vec3 ex_viewDirection;

void main(void) {
   ex_worldPosition = modelMatrix * vec4(in_Position, 1.0f);
   mat4 normalMatrix = transpose(inverse(modelMatrix));
   ex_worldNormal = normalize(vec3(normalMatrix * vec4(in_Normal, 0.0)));
   gl_Position = projectionMatrix * viewMatrix * ex_worldPosition;

   ex_lightDirection = normalize(lightPosition - vec3(ex_worldPosition));
   vec3 cameraPosition = vec3(inverse(viewMatrix)[3]); // Invert viewMatrix to get camera position
   ex_viewDirection = normalize(cameraPosition - vec3(ex_worldPosition));
}

