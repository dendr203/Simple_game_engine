#version 400

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

uniform vec4 ambientLight;
uniform vec4 objectColor;

out vec4 out_Color;

void main(void) {
    out_Color = objectColor;
    //out_Color = ambient * objectColor;
}
