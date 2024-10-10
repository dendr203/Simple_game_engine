#include "DrawableObject.h"

const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"out vec3 frag_pos;"
"void main () {"
"     gl_Position = vec4 (vp, 1.0);"
"	  frag_pos = vp;"
"}";

const char* vertex_shader_with_color =
"#version 330\n"
"layout(location=0) in vec4 position;\n"  // Pozice vrcholu
"layout(location=1) in vec4 color;\n"     // Barva vrcholu
"out vec4 vertex_color;\n"                // Pøeposíláme barvu do fragment shaderu
"void main () {\n"
"    gl_Position = position;\n"
"    vertex_color = color;\n"
"}";

const char* vertex_shader_trans =
"#version 330 core\n"
"layout(location = 0) in vec3 vp;\n"  // Deklarace vstupní pozice vrcholu
"layout(location = 1) in vec4 color;\n"  // Deklarace vstupní barvy
"uniform mat4 modelMatrix;\n"  // Uniformní promìnná pro transformaèní matici
"out vec4 vertex_color;\n"  // Výstupní promìnná pro barvu vrcholu
"void main() {\n"
"    gl_Position = modelMatrix * vec4(vp, 1.0);\n"  // Výpoèet pozice vrcholu
"    vertex_color = color;\n"  // Pøedání barvy do fragment shaderu
"}";




const char* fragment_shader =
"#version 330\n"
"in vec3 frag_pos;"
"out vec4 frag_colour;"
"void main () {"
"	  vec3 color = (frag_pos + vec3(0.5));"
"     frag_colour = vec4 (color, 1.0);"
"}";

const char* fragment_shader_with_color =
"#version 330\n"
"in vec4 vertex_color;\n"  // Pøijímáme barvu z vertex shaderu
"out vec4 frag_colour;\n"
"void main () {\n"
"    frag_colour = vertex_color;\n"  // Nastavujeme výslednou barvu
"}";

const char* fragment_shader_better =
"#version 330\n"
"in vec4 vertex_color;\n"  // Pøijímáme barvu z vertex shaderu
"out vec4 frag_colour;\n"
"void main () {\n"
"    frag_colour = vertex_color + 1;\n"  // Nastavujeme výslednou barvu
"}";

const char* fragment_shader_green =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.0, 0.9, 0.0, 1.0);"
"}";



DrawableObject::DrawableObject()
{
	model = new Model();
	shaderProgram = new ShaderProgram();
	transformation = new Transformation();
}

DrawableObject::~DrawableObject()
{
	
}

void DrawableObject::init_sphere()
{
	vector_model = std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0]));
	model->init_model(vector_model);
	shaderProgram->init_shader(vertex_shader_trans, fragment_shader_better);

}

void DrawableObject::init_tree()
{
	vector_model = std::vector<float>(tree, tree + sizeof(tree) / sizeof(tree[0]));
	model->init_model(vector_model);
	shaderProgram->init_shader(vertex_shader_trans, fragment_shader_with_color);
}

void DrawableObject::init_bushes()
{
	vector_model = std::vector<float>(bushes, bushes + sizeof(bushes) / sizeof(bushes[0]));
	model->init_model(vector_model);
	shaderProgram->init_shader(vertex_shader_trans, fragment_shader_green);
}

void DrawableObject::Draw()
{
	glm::mat4 modelMatrix = transformation->getModelMatrix();
	GLint modelLoc = glGetUniformLocation(shaderProgram->GetShader(), "modelMatrix");
	glUseProgram(shaderProgram->GetShader());
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &modelMatrix[0][0]);
	glBindVertexArray(model->GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, vector_model.size() / 6);
}


void DrawableObject::scale(float x, float y, float z)
{
	transformation->scale(x, y, z);
}

void DrawableObject::translate(float x, float y, float z)
{
	transformation->translate(x, y, z);
}

void DrawableObject::rotate(float angle, float x, float y, float z)
{
	transformation->rotate(angle, x, y, z);
}