#version 400

uniform samplerCube skybox; // Cube map sampler

in vec3 texCoord;

out vec4 out_Color;

void main(void) {
    // Vzorkování cube map textury na základì texCoord
    out_Color = texture(skybox, texCoord);
}
