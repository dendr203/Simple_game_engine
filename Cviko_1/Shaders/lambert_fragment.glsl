#version 400

struct Light {
    int type;

    vec3 position;
    vec3 lightC; // Light color
    vec4 ambient; // Ambient light
    float shininess;

    float constant;
    float linear;
    float quadratic;

    vec3 direction; // Only used for directional and spotlight
    float cutoff;   // Only used for spotlight (cosine of angle)
    float outerCutoff; // For smooth spotlight edges
};

uniform Light lights[10];
uniform int numberOfLights;

in vec3 worldNormal;
in vec4 fragPosition;
in vec3 viewDirection;

uniform vec4 objectColor;

out vec4 out_Color;

void main(void) {

    vec4 ambientLight = vec4(0.0);
    vec4 diffuseLight = vec4(0.0);

    for (int i = 0; i < numberOfLights; ++i)
    {
        ambientLight += lights[i].ambient;

		vec3 lightDir = normalize(lights[i].position - vec3(fragPosition));
		float dot_product = max(dot(lightDir, worldNormal), 0.0);
		diffuseLight += dot_product * vec4(lights[i].lightC, 1.0);
	}

    out_Color = (ambientLight + diffuseLight) * objectColor;
}
