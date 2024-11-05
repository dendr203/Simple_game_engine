#version 400
in vec3 worldNormal;
in vec3 lightDirection;
in vec3 viewDirection;

uniform vec3 lightColor;
uniform vec4 ambientLight;
uniform float shininess;
uniform vec4 objectColor;

out vec4 out_Color;

void main(void) {

// Compute light direction and view direction
	vec3 lightDir = normalize(lightDirection);

// Diffuse light
   float dot_product = max(dot(normalize(worldNormal), lightDirection), 0.0);
   vec4 diffuse = dot_product * vec4(lightColor, 1.0);

   vec3 halfwayVec = normalize(viewDirection + lightDirection);

   vec3 reflectDir = normalize(reflect(-lightDirection, normalize(worldNormal)));
// Specular light
   float spec = pow(max(dot(worldNormal, halfwayVec), 0.0), shininess);
   vec4 specular = vec4(lightColor, 1.0) * spec;


   if (dot(normalize(worldNormal), lightDirection) < 0.0)
   {
        specular = vec4(0.0, 0.0, 0.0, 0.0);
   }
   

   out_Color = ambientLight + (diffuse * objectColor) + specular;
};