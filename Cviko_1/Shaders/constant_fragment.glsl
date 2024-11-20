#version 400

struct Light {
    int type;

    vec3 position;
    vec3 lightC; // Light color

    float constant;
    float linear;
    float quadratic;

    vec3 direction; // Only used for directional and spotlight
    float cutoff;   // Only used for spotlight (cosine of angle)
    float outerCutoff; // For smooth spotlight edges
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

uniform vec4 objectColor;
uniform sampler2D textureSampler;
uniform bool useTexture;

in vec2 texCoord;

out vec4 out_Color;

void main(void)
{
    vec4 textureColor = vec4(1.0, 1.0, 1.0, 1.0);
    if(useTexture)
    {
        textureColor = texture(textureSampler, texCoord);    
    }

    out_Color = textureColor * objectColor;
}
