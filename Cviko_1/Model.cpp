#include "Model.h"
Model::Model()
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
}

Model::~Model() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Model::init_model(const std::vector<float>& vector_model)
{
	model = vector_model;
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, model.size() * sizeof(float), model.data(), GL_STATIC_DRAW);
	
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1); //colors from fragment shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0); //pozice
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(sizeof(float) * 3)); // barva
}

void Model::draw_model(){
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, model.size() / 6); // Or any number based on vertices count
}	
