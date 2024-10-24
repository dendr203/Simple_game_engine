#version 400

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
in vec3 ex_lightDirection;
in vec3 ex_viewDirection;

uniform vec3 lightColor;
uniform vec4 ambientLight;
uniform float shininess;

out vec4 out_Color;

void main(void) {
   vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);

   // Compute light direction and view direction
   vec3 lightDir = normalize(ex_lightDirection);

   // Diffuse light
   float dot_product = max(dot(normalize(ex_worldNormal), ex_lightDirection), 0.0);
   vec4 diffuse = dot_product * vec4(lightColor, 1.0);

   // Specular light
   vec3 reflectDir = normalize(reflect(-ex_lightDirection, normalize(ex_worldNormal)));
   float spec = pow(max(dot(ex_viewDirection, reflectDir), 0.0), shininess);
   vec4 specular = vec4(lightColor, 1.0) * spec;

   out_Color = ambientLight + (diffuse * objectColor) + specular;
}