#version 400

struct Light {
    int type;

    vec3 position;
    vec3 lightC; 

    float constant;
    float linear;
    float quadratic;

    vec3 direction; 
    float cutoff;   
    float outerCutoff; 
};
uniform Light lights[10];
uniform int numberOfLights;


struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material material;


in vec3 worldNormal;
in vec4 fragPosition;
in vec3 viewDirection;

uniform vec4 objectColor;

out vec4 out_Color;

void main(void) {

    vec4 ambientLight = vec4(material.ambient * lights[0].lightC, 1.0);
    vec4 finalColor = vec4(0.0);


    for (int i = 0; i < numberOfLights; ++i)
    {
		vec3 lightDir = vec3(0.0);
        float attenuation = 1.0;

        
        if (lights[i].type == 0) // Bodové svìtlo
        { 
            lightDir = normalize(lights[i].position - vec3(fragPosition));
            float distance = length(lights[i].position - vec3(fragPosition));
            attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * (distance * distance));
        }
        else if (lights[i].type == 1) // Smìrové svìtlo
        { 
            lightDir = normalize(-lights[i].direction);
        }
        else if (lights[i].type == 2) // Spotlight
        { 
            lightDir = normalize(lights[i].position - vec3(fragPosition));
            float theta = dot(lightDir, normalize(-lights[i].direction)); // Kosinus úhlu mezi smìrem svìtla a fragmentem

            float innerCutoff = cos(radians(lights[i].cutoff));
            float outerCutoff = cos(radians(lights[i].outerCutoff));
          
            float intensity = clamp((theta - outerCutoff) / (innerCutoff - outerCutoff), 0.0, 1.0);
            //intensity = max(intensity, 0.1);

            if (theta >= innerCutoff)
            {
                attenuation *= intensity;
            }
            else if (theta >= outerCutoff)
			{
                attenuation *= intensity;
			}
            else
            {
                attenuation = 0.;
            }
        }

        // Diffuse light (Lambertùv model)
        float dot_product = max(dot(lightDir, worldNormal), 0.0);
        vec4 diffuse = dot_product * vec4(material.diffuse * lights[i].lightC, 1.0);


        finalColor += diffuse * attenuation;
	}

    out_Color = (ambientLight + finalColor) * objectColor;
}
