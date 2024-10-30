#version 400

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec4 ambientLight;
uniform vec4 objectColor;

out vec4 out_Color;

void main(void) {
    vec3 lightDirection = lightPosition - vec3(ex_worldPosition);

    float dot_product = max(dot(normalize(lightDirection), normalize(ex_worldNormal)), 0.0);
    vec4 diffuse = dot_product * vec4(lightColor, 1.0); // Difuzní osvìtlení

    out_Color = (ambientLight + diffuse) * objectColor;
}
