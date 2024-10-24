#version 400

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

uniform vec4 ambientLight; 

out vec4 out_Color;

void main(void) {
    out_Color = ambientLight * vec4(0.385, 0.647, 0.812, 1.0);
}
