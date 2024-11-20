#version 400

uniform samplerCube skybox; // Cube map sampler

in vec3 texCoord;

out vec4 out_Color;

void main(void) {
    // Vzorkov�n� cube map textury na z�klad� texCoord
    out_Color = texture(skybox, texCoord);
}
