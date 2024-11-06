#version 400

struct Light {
    vec3 position;
    vec3 lightC; // Light color
    vec4 ambient; // Ambient light
    float shininess;
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

//      Diffuse light
        float diff = max(dot(normal, lightDir), 0.0);
        vec4 diffuse = diff * vec4(lights[i].lightC, 1.0); //* objectColor;



//      Specular light
        //vec3 halfwayVec = normalize(lightDir + normal);
        vec3 reflectDir = reflect(-lightDir, normal);


        float spec = 0.0;
        if (diff > 0.0) { 
            spec = pow(max(dot(viewDirection, reflectDir), 0.0), lights[i].shininess);
        }
        vec4 specular = vec4(lights[i].lightC, 1.0) * spec;
   
        finalColor += lights[i].ambient + (diffuse * objectColor) + specular;
        //finalColor += lights[i].ambient + diffuse + specular;
    }

    out_Color = finalColor;
    //out_Color = ambientLight + (diffuse * objectColor) + specular;
};