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
    vec3 normal = normalize(worldNormal);
    vec4 finalColor = vec4(0.0);
    vec3 fragPosition = vec3(fragPosition);

    for (int i = 0; i < numberOfLights; ++i) {

        vec3 lightDir = normalize(lights[i].position - fragPosition);
        float attenuation = 1.0;
        float theta = 0.0;

        if(lights[i].type == 0) //point light
        {
            float distance = length(lights[i].position - fragPosition);
            attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * (distance * distance));
        } 
        else if (lights[i].type == 1) //directional light
        {
            attenuation = 1.0;
        
        }
        else if (lights[i].type == 2) //spotlight
        {   
            float distance = length(lights[i].position - fragPosition);
            attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * (distance * distance));
            
            
            theta = dot(-lightDir, normalize(lights[i].direction));
            if (theta > cos(radians(lights[i].cutoff)))
            {
                attenuation = 0.9;
            } 
            else if (theta > cos(radians(lights[i].outerCutoff)))
            {
                float intensity = (theta - cos(radians(lights[i].outerCutoff))) / (cos(radians(lights[i].cutoff)) - cos(radians(lights[i].outerCutoff)));
                attenuation = intensity;
            }
            else
            {
                attenuation = 0.1;
            }
        }

        
	    


        // Diffuse light
        float diff = max(dot(lightDir, normal), 0.0);
        vec4 diffuse = diff * vec4(lights[i].lightC, 1.0); //* objectColor;


        //Specular light
        //vec3 halfwayVec = normalize(lightDir + normal);
        vec3 reflectDir = reflect(-lightDir, normal);

        float spec;
        if (diff > 0.0)
        {
			spec = pow(max(dot(viewDirection, reflectDir), 0.0), lights[i].shininess);
		}
        vec4 specular = vec4(lights[i].lightC, 1.0) * spec;

        finalColor += (lights[i].ambient + (diffuse + specular) * attenuation) * objectColor;
        
    }



    out_Color = finalColor;
    
};