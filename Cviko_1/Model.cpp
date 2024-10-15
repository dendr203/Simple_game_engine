#include "Model.h"
Model::Model() { }

Model::~Model() { }

void Model::init_model(std::vector<float>& vector_model)
{
	model = vector_model;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, model.size() * sizeof(float), model.data(), GL_STATIC_DRAW);


	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1); //barvy pøímo ze struktury z fragment shaderu
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0); //pozice
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(sizeof(float) * 3)); // barva
}


GLuint Model::GetVAO()
{
	return VAO;
}	
