#version 400
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
in vec3 ex_lightDirection;
in vec3 ex_viewDirection;

uniform vec3 lightColor;
uniform vec4 ambientLight;
uniform float shininess;
uniform vec4 objectColor;

out vec4 out_Color;

void main(void) {

// Compute light direction and view direction
	vec3 lightDir = normalize(ex_lightDirection);

// Diffuse light
   float dot_product = max(dot(normalize(ex_worldNormal), ex_lightDirection), 0.0);
   vec4 diffuse = dot_product * vec4(lightColor, 1.0);

	vec3 halfwayVec = normalize(ex_viewDirection + ex_lightDirection);

   vec3 reflectDir = normalize(reflect(-ex_lightDirection, normalize(ex_worldNormal)));
// Specular light
   float spec = pow(max(dot(ex_worldNormal, halfwayVec), 0.0), shininess);
   vec4 specular = vec4(lightColor, 1.0) * spec;

   out_Color = ambientLight + (diffuse * objectColor) + specular;
};