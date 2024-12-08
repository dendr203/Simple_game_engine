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
uniform sampler2D textureSampler;
uniform bool useTexture;

in vec2 texCoord;


struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material material;


in vec3 worldNormal;        //normal in world coordinates
in vec4 fragPosition;       //position of the fragment in world coordinates
in vec3 viewDirection;      //direction from the fragment to the camera

uniform vec4 objectColor;

out vec4 out_Color;

void main(void) {
    
    // Ambient lighting (outside of the loop, as it does not depend on specific lights)
    vec4 ambientLight = vec4(material.ambient * lights[0].lightC, 1.0);
    vec4 finalColor = vec4(0.0);

    vec4 textureColor = vec4(1.0, 1.0, 1.0, 1.0);
    if(useTexture)
    {
        textureColor = texture(textureSampler, texCoord);    
    }


    for (int i = 0; i < numberOfLights; ++i)
    {      
        vec3 lightDir = vec3(0.0);
        float attenuation = 1.0;

        if(lights[i].type == 0) //point light
        {
            lightDir = normalize(lights[i].position - vec3(fragPosition));
            float distance = length(lights[i].position - vec3(fragPosition));
            attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * (distance * distance));
        } 
        else if (lights[i].type == 1) //directional light
        {
            lightDir = normalize(-lights[i].direction);
        }
        else if (lights[i].type == 2) //spotlight
        {   
            //pro spotlight je to smìr svìtla k fragmentu, proto se použije poté pøi theta -lightDir
            lightDir = normalize(lights[i].position - vec3(fragPosition));
            float theta = dot(lightDir, normalize(-lights[i].direction));

            float innerCutoff = cos(radians(lights[i].cutoff));
            float outerCutoff = cos(radians(lights[i].outerCutoff));

            float intensity = clamp((theta - outerCutoff) / (innerCutoff - outerCutoff), 0.0, 1.0);

            attenuation*= intensity;
        }


        // Diffuse light (Lambertùv model)
        // intenzita svìtla je tedy závislá na úhlu mezi svìtelným paprskem a normálou povrchu
        // difùzní složka je jen odražené svìtlo od matného povrchu
        float diff = max(dot(lightDir, worldNormal), 0.0);
        vec4 diffuse = diff * vec4(material.diffuse * lights[i].lightC, 1.0) * textureColor;


        //Specular light
        //nejdøíve spoèítáme polovièní vektor mezi smìrem pohledu a smìrem svìtla
        vec3 halfwayVec = normalize(lightDir + viewDirection);
        float spec = 0.0;
        if (diff > 0.0)
        {
			spec = pow(max(dot(worldNormal, halfwayVec), 0.0), material.shininess);
            spec = min(spec, 1.0);
		}
        vec4 specular = vec4(material.specular * lights[i].lightC, 1.0) * spec;

        finalColor += (diffuse + specular) * attenuation;
        
    }
    out_Color = (ambientLight + finalColor) * objectColor;

    //v pravo (kladné x) - èervená
    //nahoru (kladné y) - zelená
    //dopøedu (kladné z) - modrá
    //out_Color = vec4((worldNormal + 1.0) * 0.5, 1.0);  // Vizualizace normál

};