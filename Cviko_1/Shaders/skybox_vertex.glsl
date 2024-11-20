#version 400

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(location = 0) in vec3 in_Position;

out vec3 texCoord;

void main(void) {
    // Odstranìní translaèní složky z viewMatrix pro fixní pozici skyboxu
    mat4 view = mat4(mat3(viewMatrix));

    gl_Position = projectionMatrix * view * vec4(in_Position, 1.0f);
    texCoord = in_Position;
}
