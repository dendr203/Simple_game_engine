#pragma once
#include "Model.h"


class Triangle : public Model
{
public:
	Triangle();

	void Init(const char* vertex_shader, const char* fragment_shader) override;

private:
	float points[9];
	int size = 9 * sizeof(float);
};

