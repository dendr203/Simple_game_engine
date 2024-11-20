#include "TexturedModel.h"

TexturedModel::TexturedModel(const std::vector<float>& vertices, Texture* texture, float tex_scale, int is_skybox)
	: Model(vertices), texture(texture), tex_scale(tex_scale)
{
	numVertices = vertices.size() / 8;

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	if (is_skybox == 1)
	{
		numVertices = vertices.size() / 3;
		init_skybox(vertices);
	}
	else
	{
		init_model(vertices);
	}
	
}



void TexturedModel::init_model(const std::vector<float>& vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));

	glBindVertexArray(0);
}

void TexturedModel::init_skybox(const std::vector<float>& vertices)
{
	// Vytvoøení bufferu pro data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	// Nastavení vertex array objektu
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);  // Aktivace atributu
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);  // Pozice

	glBindVertexArray(0);  // Uvolnìní VAO
}



void TexturedModel::draw_model()
{
	texture->Bind();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
	texture->Unbind();
}

float TexturedModel::getScale()
{
	return tex_scale;
}



