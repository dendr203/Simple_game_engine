#include "Model.h"
void Model::Init(const char* vertex_shader, const char* fragment_shader) {}

GLuint Model::GetShader() { return shader.GetShader_prg(); }

GLuint Model::GetVBO() { return VBO.GetVBO(); }

GLuint Model::GetVAO() { return VAO.GetVAO(); }
