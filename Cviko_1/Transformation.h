#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Transformation
{
public:
	Transformation();
	~Transformation();
	void translate(float x, float y, float z);
	void rotate(float angle, float x, float y, float z);
	void scale(float x, float y, float z);
	void clearModelMatrix();

	glm::mat4 getModelMatrix() const;

private:
	glm::mat4 modelMatrix;
};

