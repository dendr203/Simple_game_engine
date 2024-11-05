#include "Model.h"
Model::Model(const std::vector<float>& vertices)
{
	numVertices = vertices.size() / 6;

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	init_model(vertices);
}

Model::~Model() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Model::init_model(const std::vector<float>& verticies)
{
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float), verticies.data(), GL_STATIC_DRAW);
	
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1); // colors from fragment shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0); // position
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(sizeof(float) * 3)); // color
}

void Model::draw_model(){
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, numVertices); // Or any number based on vertices count
}	
