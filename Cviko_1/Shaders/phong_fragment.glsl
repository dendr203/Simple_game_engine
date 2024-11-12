#version 400

struct Light {
    int type;            // Typ sv�tla (bodov�, sm�rov�, atd.)
    vec3 position;       // Pozice sv�tla (pouze pro bodov� sv�tla)
    vec3 lightC;         // Barva sv�tla
    vec4 ambient;        // Ambientn� sv�tlo
    float shininess;     // Shininess pro spekul�rn� slo�ku
    float constant;      // Konstantn� komponenta pro sv�teln� pokles (pro bodov� sv�tla)
    float linear;        // Line�rn� komponenta pro pokles (pro bodov� sv�tla)
    float quadratic;     // Kvadratick� komponenta pro pokles (pro bodov� sv�tla)
    vec3 direction;      // Sm�r sv�tla (pouze pro sm�rov� a spotlight sv�tla)
    float cutoff;        // �hel pro spotlight (kosinus �hlu)
    float outerCutoff;   // Pro plynul� hrany pro spotlight
};

uniform Light lights[10];
uniform int numberOfLights;

in vec3 worldNormal;
in vec4 fragPosition;
in vec3 viewDirection;

uniform vec4 objectColor;

out vec4 out_Color;

void main(void) {
    vec4 finalColor = vec4(0.0, 0.0, 0.0, 1.0); // Inicializace barvy na �ernou (bez osv�tlen�)

    // Iterace p�es v�echna sv�tla
    for (int i = 0; i < numberOfLights; ++i) {
        vec3 lightDir;  // Sm�r sv�tla pro dan� sv�tlo

        // V�po�et sm�ru sv�tla podle typu sv�tla
        if (lights[i].type == 0) { // Bodov� sv�tlo
            lightDir = normalize(lights[i].position - fragPosition.xyz);
        } else if (lights[i].type == 1) { // Sm�rov� sv�tlo
            lightDir = normalize(-lights[i].direction); // Negace pro sm�r
        } else if (lights[i].type == 2) { // Spotlight
            lightDir = normalize(lights[i].position - fragPosition.xyz);
        }

        // Difuzn� slo�ka (Lambertovo osv�tlen�)
        float dot_product = max(dot(normalize(worldNormal), lightDir), 0.0);
        vec4 diffuse = dot_product * vec4(lights[i].lightC, 1.0);

        // Spekul�rn� slo�ka (Phong�v model)
        vec3 reflectDir = normalize(reflect(-lightDir, normalize(worldNormal)));
        float spec = pow(max(dot(viewDirection, reflectDir), 0.0), lights[i].shininess);
        vec4 specular = vec4(lights[i].lightC, 1.0) * spec;

        // Pro bodov� sv�tla aplikujeme pokles intenzity podle vzd�lenosti
        if (lights[i].type == 0) { // P�edpokl�d�m, �e 0 znamen� bodov� sv�tlo
            float distance = length(fragPosition.xyz - lights[i].position);
            float attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * (distance * distance));
            diffuse *= attenuation;
            specular *= attenuation;
        }

        // Aplikace pro sm�rov� a spotlight sv�tla (pro spotlight p�id�v�me �pravy)
        if (lights[i].type == 1 || lights[i].type == 2) { // Sm�rov� nebo spotlight sv�tlo
            // Pro spotlight: kontrolujeme, zda je �hel mezi sm�rem sv�tla a sm�rem k fragmentu v platn�m rozsahu
            if (lights[i].type == 2)
            {
                float theta = dot(lightDir, normalize(lights[i].direction)); // Vypo��t�me �hel
                if (theta > lights[i].cutoff)
                {
                    float epsilon = lights[i].cutoff - lights[i].outerCutoff;
                    float intensity = clamp((theta - lights[i].outerCutoff) / epsilon, 0.0, 1.0);
                    diffuse *= intensity;
                    specular *= intensity;
                } else
                {
                    continue;  // Pokud je sv�tlo mimo �hel, ignorujeme ho
                }
            }
        }

        // P�id�n� v�sledn�ch slo�ek (difuzn�, spekul�rn�) k celkov� barv�
        finalColor += (diffuse * objectColor) + specular;
    }

    out_Color = finalColor;  // V�stupn� barva
}
