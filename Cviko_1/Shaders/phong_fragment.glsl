#version 400

struct Light {
    int type;            // Typ svìtla (bodové, smìrové, atd.)
    vec3 position;       // Pozice svìtla (pouze pro bodová svìtla)
    vec3 lightC;         // Barva svìtla
    vec4 ambient;        // Ambientní svìtlo
    float shininess;     // Shininess pro spekulární složku
    float constant;      // Konstantní komponenta pro svìtelný pokles (pro bodová svìtla)
    float linear;        // Lineární komponenta pro pokles (pro bodová svìtla)
    float quadratic;     // Kvadratická komponenta pro pokles (pro bodová svìtla)
    vec3 direction;      // Smìr svìtla (pouze pro smìrová a spotlight svìtla)
    float cutoff;        // Úhel pro spotlight (kosinus úhlu)
    float outerCutoff;   // Pro plynulé hrany pro spotlight
};

uniform Light lights[10];
uniform int numberOfLights;

in vec3 worldNormal;
in vec4 fragPosition;
in vec3 viewDirection;

uniform vec4 objectColor;

out vec4 out_Color;

void main(void) {
    vec4 finalColor = vec4(0.0, 0.0, 0.0, 1.0); // Inicializace barvy na èernou (bez osvìtlení)

    // Iterace pøes všechna svìtla
    for (int i = 0; i < numberOfLights; ++i) {
        vec3 lightDir;  // Smìr svìtla pro dané svìtlo

        // Výpoèet smìru svìtla podle typu svìtla
        if (lights[i].type == 0) { // Bodové svìtlo
            lightDir = normalize(lights[i].position - fragPosition.xyz);
        } else if (lights[i].type == 1) { // Smìrové svìtlo
            lightDir = normalize(-lights[i].direction); // Negace pro smìr
        } else if (lights[i].type == 2) { // Spotlight
            lightDir = normalize(lights[i].position - fragPosition.xyz);
        }

        // Difuzní složka (Lambertovo osvìtlení)
        float dot_product = max(dot(normalize(worldNormal), lightDir), 0.0);
        vec4 diffuse = dot_product * vec4(lights[i].lightC, 1.0);

        // Spekulární složka (Phongùv model)
        vec3 reflectDir = normalize(reflect(-lightDir, normalize(worldNormal)));
        float spec = pow(max(dot(viewDirection, reflectDir), 0.0), lights[i].shininess);
        vec4 specular = vec4(lights[i].lightC, 1.0) * spec;

        // Pro bodová svìtla aplikujeme pokles intenzity podle vzdálenosti
        if (lights[i].type == 0) { // Pøedpokládám, že 0 znamená bodové svìtlo
            float distance = length(fragPosition.xyz - lights[i].position);
            float attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * (distance * distance));
            diffuse *= attenuation;
            specular *= attenuation;
        }

        // Aplikace pro smìrové a spotlight svìtla (pro spotlight pøidáváme úpravy)
        if (lights[i].type == 1 || lights[i].type == 2) { // Smìrové nebo spotlight svìtlo
            // Pro spotlight: kontrolujeme, zda je úhel mezi smìrem svìtla a smìrem k fragmentu v platném rozsahu
            if (lights[i].type == 2)
            {
                float theta = dot(lightDir, normalize(lights[i].direction)); // Vypoèítáme úhel
                if (theta > lights[i].cutoff)
                {
                    float epsilon = lights[i].cutoff - lights[i].outerCutoff;
                    float intensity = clamp((theta - lights[i].outerCutoff) / epsilon, 0.0, 1.0);
                    diffuse *= intensity;
                    specular *= intensity;
                } else
                {
                    continue;  // Pokud je svìtlo mimo úhel, ignorujeme ho
                }
            }
        }

        // Pøidání výsledných složek (difuzní, spekulární) k celkové barvì
        finalColor += (diffuse * objectColor) + specular;
    }

    out_Color = finalColor;  // Výstupní barva
}
