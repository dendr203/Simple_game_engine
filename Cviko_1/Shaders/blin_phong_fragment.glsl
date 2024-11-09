#version 400

struct Light {
    vec3 position;
    vec3 lightC; // Light color
    vec4 ambient; // Ambient light
    float shininess;

    float constant;
    float linear;
    float quadratic;
};

uniform Light lights[2];
uniform int numberOfLights;

in vec3 worldNormal;
in vec3 fragPosition;
in vec3 viewDirection;

uniform vec4 objectColor;

out vec4 out_Color;

void main(void) {
    vec3 normal = normalize(worldNormal);
    vec4 finalColor = vec4(0.0);

    for (int i = 0; i < numberOfLights; ++i) {

//      Compute light direction
	    vec3 lightDir = normalize(lights[i].position - fragPosition);

//      Compute attenuation
        float distance = length(lights[i].position - fragPosition);
        float attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * (distance * distance));

//      Diffuse light
        float diff = max(dot(lightDir, normal), 0.0);
        vec4 diffuse = diff * vec4(lights[i].lightC, 1.0); //* objectColor;


//      Specular light
        //vec3 halfwayVec = normalize(lightDir + normal);
        vec3 reflectDir = reflect(-lightDir, normal);

        
        float spec;
        if (diff > 0.0)
        {
			spec = pow(max(dot(viewDirection, reflectDir), 0.0), lights[i].shininess);
		}

        vec4 specular = vec4(lights[i].lightC, 1.0) * spec;

        //float spec = pow(max(dot(viewDirection, reflectDir), 0.0), lights[i].shininess);
        //float specSmooth = smoothstep(0.0, 0.1, spec); // Adjust smoothness threshold
        //vec4 specular = vec4(lights[i].lightC, 1.0);

        finalColor += (lights[i].ambient + (diffuse + specular) * attenuation) * objectColor;
        //finalColor += lights[i].ambient + diffuse + specular;
    }

    out_Color = finalColor;
    //out_Color = ambientLight + (diffuse * objectColor) + specular;
};